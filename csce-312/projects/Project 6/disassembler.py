import re
from sys import stdin
# Correctly disassembles well-formed Hack machine code
# into valid Hack assembly code.


# def destructSymbolTable():


def compTable():
    compTable = dict()
    compTable["0101010"] = "0"
    compTable["0111111"] = "1"
    compTable["0111010"] = "-1"
    compTable["0001100"] = "D"
    compTable["0110000"] = "A"
    compTable["1110000"] = "M"
    compTable["0001101"] = "!D"
    compTable["0110001"] = "!A"
    compTable["1110001"] = "!M"
    compTable["0001111"] = "-D"
    compTable["0110011"] = "-A"
    compTable["1110011"] = "-M"
    compTable["0011111"] = "D+1"
    compTable["0110111"] = "A+1"
    compTable["1110111"] = "M+1"
    compTable["0001110"] = "D-1"
    compTable["0110010"] = "A-1"
    compTable["1110010"] = "M-1"
    compTable["0000010"] = "D+A"
    compTable["1000010"] = "D+M"
    compTable["0010011"] = "D-A"
    compTable["1010011"] = "D-M"
    compTable["0000111"] = "A-D"
    compTable["1000111"] = "M-D"
    compTable["0000000"] = "D&A"
    compTable["1000000"] = "D&M"
    compTable["0010101"] = "D|A"
    compTable["1010101"] = "D|M"
    return compTable


def destTable():
    destTable = dict()
    destTable["001"] = "M"
    destTable["010"] = "D"
    destTable["011"] = "MD"
    destTable["100"] = "A"
    destTable["101"] = "AM"
    destTable["110"] = "AD"
    return destTable


def jumpTable():
    jumpTable = dict()
    jumpTable["001"] = "JGT"
    jumpTable["010"] = "JEQ"
    jumpTable["011"] = "JGE"
    jumpTable["100"] = "JLT"
    jumpTable["101"] = "JNE"
    jumpTable["110"] = "JLE"
    jumpTable["111"] = "JMP"
    return jumpTable


def AInstruction(line):
    # convert binary -> decimal
    # then prepend '@'
    decimal = 0
    line = line.rstrip()
    for i in line:
        decimal = int(i) + decimal*2
    answer = "@" + str(decimal)
    return answer


def CInstruction(line):
    result = ""
    # break binary into 3 parts
    comp_token = line[3:10]
    # print(comp_token)
    dest_token = line[10:13]
    # print(dest_token)
    jump_token = line[13:16]
    # print(jump_token)
    # add either '=' , ';' ,both, or none
    if(jump_token != "000" and dest_token != "000"):  # both
        result = destTable[dest_token] + "=" + \
            compTable[comp_token] + ";" + jumpTable[jump_token]
        return result
    elif(jump_token != "000"):  # just ;
        result = compTable[comp_token] + ";" + jumpTable[jump_token]
        return result
    elif(jump_token == "000" and dest_token != "000"):  # just =
        result = destTable[dest_token] + "=" + compTable[comp_token]
        return result
    else:  # none
        result = compTable[comp_token]
        return result


# main
compTable = compTable()
destTable = destTable()
jumpTable = jumpTable()


def main():

    # variables and labels
    all_stdin = []
    for line in stdin:
        all_stdin.append(line)

    for line in all_stdin:
        if (line == ""):
            continue
        if (line[0:1] == "0"):
            binary = AInstruction(line)  # translating to binary
            print(binary)  # stdout
            continue
        else:
            binary = CInstruction(line)
            print(binary)
            continue


main()