#ifndef WEATHERFUNCTIONS_H
#define WEATHERFUNCTIONS_H
#include <string>
using std::string, std::ifstream;
// add function declarations/prototypes
double **add_cities_from_file(double **table, size_t &city, size_t &days, string filename);
void destroy_table(double **table, size_t city);
double get_average_rainfall_between_days_given_city(double **table, size_t city, size_t days, size_t start_day_index, size_t end_day_index, size_t city_index);
double get_average_rainfall_between_days_all_cities(double **table, size_t city, size_t days, size_t start_day_index, size_t end_day_index);
double get_max_rainfall_all_cities_given_day(double **table, size_t city, size_t days, size_t index_day);
double get_max_rainfall_given_city(double **table, size_t city, size_t days, size_t city_index);
#endif