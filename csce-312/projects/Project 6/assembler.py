import re
from sys import stdin


def createSymbolTable(all_stdin):
    symbolTable = dict()
    symbolTable["SP"] = 0
    symbolTable["LCL"] = 1
    symbolTable["ARG"] = 2
    symbolTable["THIS"] = 3
    symbolTable["THAT"] = 4

    for r in range(0, 16, 1):
        symbolTable["R" + str(r)] = r

    symbolTable["SCREEN"] = 16384
    symbolTable["KBD"] = 24576

    #filelines = sys.stdin.readlines()
    pc = 0

    for line in all_stdin:
        clean = removeCommentsAndWhitespace(line)  # TODO
        if (isLabel(clean)):  # TODO

            label = removeParanthesis(clean)  # TODO

            if (not label in symbolTable):
                symbolTable[label] = pc

        if (isInstruction(clean)):
            pc = pc + 1
 # TODO
    # file = openFile(assemblyFileName)
    nextAddress = 16
    for line in all_stdin:
        clean = removeCommentsAndWhitespace(line)
        if (isAInstruction(clean)):  # TODO
            AInstructionVal = clean.strip("@")
            if ((not AInstructionVal.isnumeric()) and (not AInstructionVal in symbolTable)):
                symbolTable[AInstructionVal] = nextAddress
                nextAddress = nextAddress + 1
    return symbolTable


def createCompTable():
    compTable = dict()

    compTable["0"] = "0101010"
    compTable["1"] = "0111111"
    compTable["-1"] = "0111010"
    compTable["D"] = "0001100"
    compTable["A"] = "0110000"
    compTable["M"] = "1110000"
    compTable["!D"] = "0001101"
    compTable["!A"] = "0110001"
    compTable["!M"] = "1110001"
    compTable["-D"] = "0001111"
    compTable["-A"] = "0110011"
    compTable["-M"] = "1110011"
    compTable["D+1"] = "0011111"
    compTable["A+1"] = "0110111"
    compTable["M+1"] = "1110111"
    compTable["D-1"] = "0001110"
    compTable["A-1"] = "0110010"
    compTable["M-1"] = "1110010"
    compTable["D+A"] = "0000010"
    compTable["D+M"] = "1000010"
    compTable["D-A"] = "0010011"
    compTable["D-M"] = "1010011"
    compTable["A-D"] = "0000111"
    compTable["M-D"] = "1000111"
    compTable["D&A"] = "0000000"
    compTable["D&M"] = "1000000"
    compTable["D|A"] = "0010101"
    compTable["D|M"] = "1010101"
    return compTable


def createDestTable():
    destTable = dict()
    destTable["M"] = "001"
    destTable["D"] = "010"
    destTable["MD"] = "011"
    destTable["A"] = "100"
    destTable["AM"] = "101"
    destTable["AD"] = "110"
    return destTable


def createJumpTable():
    jumpTable = dict()
    jumpTable["JGT"] = "001"
    jumpTable["JEQ"] = "010"
    jumpTable["JGE"] = "011"
    jumpTable["JLT"] = "100"
    jumpTable["JNE"] = "101"
    jumpTable["JLE"] = "110"
    jumpTable["JMP"] = "111"
    return jumpTable


def removeCommentsAndWhitespace(line):
    line = line.replace(" ", "")  # removes whitespace
    line = line.rstrip("//")  # removes comment
    line = line.rstrip("\n")
    return line


def removeParanthesis(clean):
    clean = clean.replace("(", "")  # removes leftmost paranthesis
    clean = clean.replace(")", "")  # removes rightmost paranthesis
    return clean


def isLabel(clean):  # if it is a label : something surrounded by paranthesis
    if(clean.startswith("(") and clean.endswith(")")):
        return True
    return False


def isInstruction(clean):  # Not an empty line, not a comment
    if(not clean == "" and not clean.startswith("//")):
        return True
    return False


def validSymbolChars(dropAt):
    if re.match("^[A-Za-z0-9_-]*$", dropAt):
        return True
    return False


def toBinary15Bit(dropAt):
    binary = "{0:b}".format(int(dropAt))
    while(len(binary) < 15):
        binary = "0" + binary
    return binary


def isAInstruction(line):
    if (len(line) > 0 and line[0] != '@'):
        return False

    dropAt = line[1: len(line) - 1]

    if (dropAt.isdigit()):  # constant
        if(int(dropAt) >= 0):
            return True

    # symbol cannot begin with a digit
    if (len(dropAt) > 0 and dropAt[0].isdigit()):
        return False

    # TODO : symbol checks if alpahbetical or colon,_,etc.
    if (validSymbolChars(dropAt)):
        return True
    return False

# translate Ainstruction


def aInstruction(line, symbolTable):  # assume valid A instruction
    dropAt = line[1: len(line)]
    # print("dropAt: ", dropAt)
    if (dropAt.isdigit()):  # constant
        if(int(dropAt) >= 0):
            binary = toBinary15Bit(dropAt)  # TODO
            return ('0' + binary)
    addr = symbolTable[dropAt]
    binary = toBinary15Bit(addr)
    return ('0' + binary)


def isCInstruction(line):

    # tokens=splitStringAtChars(line, ['=', ';'])  # TODO
    tokens = re.split("=|;", line)

    if (len(tokens) != 2 and len(tokens) != 3 and len(tokens) != 1):
        return False
    elif(len(tokens) == 1):
        # comp
        if(not tokens[0] in compTable):
            return False

    elif (len(tokens) == 2):
        if (line.count("=") == 1):
            # dest and comp
            if (not tokens[0] in destTable):
                return False
            if (not tokens[1] in compTable):
                return False
        else:
            # comp and jump
            if (not tokens[0] in compTable):
                return False
            if (not tokens[1] in jumpTable):
                return False
    else:
        # dest, comp, jump present
        if (not tokens[0] in destTable):
            return False

        if (not tokens[1] in compTable):
            return False

        if (not tokens[2] in jumpTable):
            return False

    return True


def cInstruction(line):
    # tokens = splitStringAtChars(line, ['=', ';'])
    tokens = re.split("=|;", line)
    prefix = "111"
    dest = ""
    comp = ""
    jump = ""

    if(len(tokens) == 1):
        # comp
        comp = compTable[tokens[0]]
        dest = "000"
        jump = "000"
    elif (len(tokens) == 2):
        if (line.count("=") == 1):
            # dest and comp
            dest = destTable[tokens[0]]
            comp = compTable[tokens[1]]
            jump = "000"
        else:
            # comp and jump
            dest = "000"
            comp = compTable[tokens[0]]
            jump = jumpTable[tokens[1]]
    else:
        # dest, comp, jump present
        dest = destTable[tokens[0]]
        comp = compTable[tokens[1]]
        jump = jumpTable[tokens[2]]
    # print(tokens)
    # print(line)
    return (prefix + comp + dest + jump)

# assembler.txt


compTable = createCompTable()
destTable = createDestTable()
jumpTable = createJumpTable()


def main():

    # variables and labels
    all_stdin = []
    for line in stdin:
        # print(line)
        all_stdin.append(line)
    symbolTable = createSymbolTable(all_stdin)

    # instructions

    # filelines = sys.stdin.readlines()
    for line in all_stdin:
        line = removeCommentsAndWhitespace(line)
        # print(line)
        if (line == ""):
            continue
        if (isAInstruction(line)):
            binary = aInstruction(line, symbolTable)  # translating to binary
            print(binary)  # stdout
            continue

        if (isCInstruction(line)):
            binary = cInstruction(line)
            print(binary)
            continue


main()