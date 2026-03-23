#pragma once
class classExample
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    classExample(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

