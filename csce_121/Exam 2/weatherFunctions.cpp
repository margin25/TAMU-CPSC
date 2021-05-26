#include <iostream>
#include "weatherFunctions.h"
#include <fstream>
#include <string>
// add function definitions
using std::cout, std::endl, std::string, std::cin, std::ifstream;

double **add_cities_from_file(double **table, size_t &cities, size_t &days, string filename)
{
    // returns pointer to a new table (i.e. two-dimensional array) on the heap with the new data
    // declare variables
    size_t file_city_rows = 0;
    size_t file_days_columns = 0;
    size_t combined_city_total = 0;
    //create file reader
    ifstream fin(filename);
    //cannot open file error
    if (!fin.is_open())
    {
        throw std::invalid_argument("invalid argument:");
    }
    //reading in rows and columns
    fin >> file_city_rows;
    fin >> file_days_columns;
    combined_city_total = file_city_rows + cities;
    if (table == nullptr)
    {
        combined_city_total = file_city_rows + cities;
        table = new double *[file_city_rows];
        //allocate output array
        for (size_t x = 0; x < file_city_rows; x++)
        {
            table[x] = new double[file_days_columns];
        }
        //set output array
        for (size_t y = 0; y < file_city_rows; y++)
        {
            for (size_t x = 0; x < file_days_columns; x++)
            {
                fin >> table[y][x];
            }
        }
        cities = file_city_rows;
        days = file_days_columns;
        return (table);
    }
    else
    {
        /* throws : invalid argument
            if the number of days in the input file is not equal to the number of days in the existing table.
        */
        if (file_days_columns != days)
        {
            throw std::invalid_argument("Invalid Argument");
        }
        // resize the table and add the new data.
        // Remember that resizing includes deallocating the old array.
        double **new_table = new double *[combined_city_total];
        for (size_t row = 0; row < combined_city_total; row++)
        {
            new_table[row] = new double[days];
        }
        // copy values from table to new_table
        for (size_t row = 0; row < cities; row++)
        {
            for (size_t col = 0; col < days; col++)
            {
                new_table[row][col] = table[row][col];
            }
        }
        for (size_t x = cities; x < combined_city_total; x++)
        {
            for (size_t y = 0; y < days; y++)
            {
                fin >> new_table[x][y];
            }
        }
        // deallocate table
        destroy_table(table, cities);
        // other changes : updates number of cities, updates number of days
        days = file_days_columns;
        cities = combined_city_total;
        // return new table
        return (new_table);
    }
    return (table);
}

void destroy_table(double **table, size_t cities)
{
    //returns void
    if (cities == 0)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (table == nullptr)
    {
        throw std::invalid_argument("invalid argument");
    }
    //Other Changes: Deallocates table from the heap
    //deallocate input array
    for (size_t x = 0; x < cities; x++)
    {
        delete[] table[x];
    }
    delete[] table;

    //Throws invalid argument:  if number of cities is zero
}

double get_average_rainfall_between_days_given_city(double **table, size_t city, size_t days, size_t start_day_index, size_t end_day_index, size_t city_index)
{
    /* throws : invalid argument 
            Invalid table (table is nullptr) 
            Invalid index of city (index >= number of cities)
            Invalid Start Day index (index >= number of days)
            Invalid End Day index (index >= number of days or index < index of start day)
    */
    if (city_index >= city)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (start_day_index >= days)
    {
        throw std::invalid_argument("invalid argument");
    }

    if (end_day_index >= days || end_day_index < start_day_index)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (table == nullptr)
    {
        throw std::invalid_argument("invalid argument");
    }
    double sum = 0.0;
    double count = 0.0;
    for (size_t i = start_day_index; i <= end_day_index; i++)
    {
        sum += table[city_index][i];
        count++;
    }

    // returns : Average rainfall for given city from start day to end day (inclusive)
    return (sum / count);
}

double get_average_rainfall_between_days_all_cities(double **table, size_t city, size_t days, size_t start_day_index, size_t end_day_index)
{
    // returns : Average rainfall for all cities between start day and end day (inclusive)
    if (table == nullptr)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (start_day_index >= days)
    {
        throw std::invalid_argument("invalid argument");
    }

    if (end_day_index >= days || end_day_index < start_day_index)
    {
        throw std::invalid_argument("invalid argument");
    }

    /* throws : invalid argument
        Invalid table (table is nullptr)
        Invalid Start Day index (index >= number of days)
        Invalid End Day index (index >= number of days or index < index of start day)
    */
    double sum = 0.0;
    double count = 0.0;
    for (size_t i = start_day_index; i <= end_day_index; i++)
    {
        for (size_t j = 0; j < city; j++)
        {
            sum += table[j][i];
            count++;
        }
    }
    return (sum / count);
}

double get_max_rainfall_all_cities_given_day(double **table, size_t cities, size_t days, size_t index_day)
{
    // returns : Maximum rainfall for all cities for the given day

    if (cities == 0)
    {
        throw std::invalid_argument("invalid argument");
    }

    if (index_day >= days)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (table == nullptr)
    {
        throw std::invalid_argument("invalid argument");
    }

    double max = table[0][0];
    for (size_t y = 0; y < cities; y++)
    {
        if (table[y][index_day] > max)
        {
            max = table[y][index_day];
        }
    }
    /* throws : invalid argument
            Invalid table (table is nullptr)
            Invalid number of cities (zero cities)
            Invalid Day index (index >= number of days)
    */

    return (max);
}

double get_max_rainfall_given_city(double **table, size_t cities, size_t days, size_t city_index)
{
    if (table == nullptr)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (days == 0)
    {
        throw std::invalid_argument("invalid argument");
    }

    if (city_index >= cities)
    {
        throw std::invalid_argument("invalid argument");
    }
    /* throws : invalid argument
            Invalid table (table is nullptr)
            Invalid number of days (zero days)
            Invalid index of city (index >= number of cities)
    */
    double max = table[0][0];
    for (size_t x = 0; x < days; x++)
    {
        if (table[city_index][x] > max)
        {
            max = table[city_index][x];
        }
    }

    return (max);
}

/* int main()
{
    size_t cities, days;
    double **table = nullptr;
    // add_cities_from_file(nullptr, cities, days, "0_cities.txt");
    // add_cities_from_file(table, cities, days, "cities1.txt");
    // table = add_cities_from_file(table, cities, days, "cities1.txt");
    // table = add_cities_from_file(table, cities, days, "cities2.txt");
    cout << days << endl;
    return (0);
} */