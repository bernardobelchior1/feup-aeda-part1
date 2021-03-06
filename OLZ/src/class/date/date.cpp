#include "date.h"

#include <sstream>
#include <stdlib.h>
#include <stdexcept>

Date::Date() {
	day = 1;
	month = 1;
	year = 1900;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	if (isDateValid(day, month, year)) {
		this->day = day;
		this->month = month;
		this->year = year;
	} else
		throw out_of_range("Invalid date.");
}

#include<iostream>

Date::Date(string date) {
	stringstream ss;
	char temp;
	ss.str(date);
	ss >> day >> temp >> month >> temp >> year;
	if (!isDateValid(day, month, year))
		throw out_of_range("Invalid date.");

}

void Date::setDay(unsigned int day) {
	if (isDateValid(day, month, year))
		this->day = day;
	else
		throw out_of_range("Invalid day.");
}

void Date::setMonth(unsigned int month) {
	if (isDateValid(day, month, year))
		this->month = month;
	else
		throw out_of_range("Invalid month.");
}

void Date::setYear(unsigned int year) {
	this->year = year;
}

unsigned int Date::getDay() const {
	return day;
}

unsigned int Date::getMonth() const {
	return month;
}

unsigned int Date::getYear() const {
	return year;
}

string Date::toString() const {
	stringstream ss;
	ss << day << '/' << month << '/' << year;
	return ss.str();
}

bool Date::isLeapYear(unsigned int year) {

	if (year % 400 == 0)
		return true;
	else if (year % 100 == 0)
		return false;
	else if (year % 4 == 0)
		return true;

	return false;
}

bool Date::isDateValid(unsigned int day, unsigned int month,
		unsigned int year) {

	if (day < 1 || day > 31 || month < 1 || month > 12)
		return false;

	switch (month) {
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
			return false;
		break;
	case 2:
		if (isLeapYear(year)) {
			if (day > 29)
				return false;
		} else {
			if (day > 28)
				return false;
		}
		break;
	}

	return true;
}

bool Date::isDateValid(const Date& date) {
	return Date::isDateValid(date.day, date.month, date.year);
}

Date& Date::operator=(Date rhs) {
	this->day = rhs.day;
	this->month = rhs.month;
	this->year = rhs.year;
	return *this;
}

ostream& operator<<(ostream& out, const Date &date){
	out << date.toString();
	return out;
}
