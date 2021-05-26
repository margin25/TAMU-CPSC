// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string &line,
                            string *category,
                            double *score);

int main()
{
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double sum_exams = 0.0;
    double num_exams = 0;
    double hw = 0.0;
    double num_hws = 0;
    double sum_lw = 0.0;
    double num_lw = 0.0;
    double sum_engagement = 0.0;
    double final_exam_score = 0.0;
    bool want_final = false;
    string line;

    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty())
    {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam")
        {
            // TODO(student): process exam score
            sum_exams += score;
            num_exams += 1;
            if (num_exams == 3 && ((sum_exams / num_exams) < 60))
            {
                sum_exams += 0;
                num_exams += 1;
            }
        }
        else if (category == "final-exam")
        {
            // TODO(student): process final exam score
            final_exam_score += score;
            want_final = true;
            if ((sum_exams / num_exams) < 60)
            {
                sum_exams += score;
                num_exams += 1;
            }
            else if (want_final == true && ((sum_exams / num_exams) >= 60))
            {
                sum_exams += score;
                num_exams += 1;
            }

            else
            {
                sum_exams += score;
                num_exams += 1;
            }
        }
        else if (category == "hw")
        {
            // TODO(student): process hw score
            hw += score;
            num_hws += 1;
        }
        else if (category == "lw")
        {
            // TODO(student): process lw score
            if (score >= 1)
            {
                sum_lw += 1;
            }

            num_lw += 1;
        }
        else if (category == "engagement")
        {
            // TODO(student): process engagement score
            sum_engagement += score;
            if (sum_engagement > 100)
            {

                sum_engagement = 100;
            }
        }
        else
        {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input

        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = 0;
    if (num_exams != 0)
    {
        exam_average = sum_exams / num_exams;
        if (final_exam_score > exam_average)
        {
            exam_average = final_exam_score;
        }
    }
    double hw_average = 0;
    if (num_hws != 0)
    {
        hw_average = hw / num_hws;
    }
    double lw_average = 0;
    if (num_lw != 0)
    {
        lw_average = (sum_lw / num_lw) * 100;
    }
    double engagement = sum_engagement;
    // TODO(student): compute weighted total of components
    double weighted_total = (exam_average * 0.4) + (hw_average * 0.4) + (lw_average * 0.1) + (engagement * 0.1);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total >= 90)
        final_letter_grade = 'A';
    else if (weighted_total >= 80)
        final_letter_grade = 'B';
    else if (weighted_total >= 70)
        final_letter_grade = 'C';
    else if (weighted_total >= 60)
        final_letter_grade = 'D';
    else
        final_letter_grade = 'F';

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions()
{
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string &line,
    string *category,
    double *score)
{
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail())
    {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade)
{
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
