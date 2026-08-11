// INFO: Headers from the standard library should be inserted at the top via
// #include <LIBRARY_NAME>
#include <cmath>
// daily_rate calculates the daily rate given an hourly rate
double daily_rate(double hourly_rate) {
    // TODO: Implement a function to calculate the daily rate given an hourly
    // rate
    return hourly_rate * 8;
}

// apply_discount calculates the price after a discount
double apply_discount(double before_discount, double discount) {
    double discount_savings,final_price;
    
    // TODO: Implement a function to calculate the price after a discount.
    discount_savings = (before_discount * discount) / 100;
    final_price = before_discount - discount_savings;
    return final_price;
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
int monthly_rate(double hourly_rate, double discount) {
    // TODO: Implement a function to calculate the monthly rate, and apply a
    // discount.
    double total_before_discount = daily_rate(hourly_rate) * 22.0;
    double final_price = apply_discount(total_before_discount, discount);
    
    // Round up to the nearest integer using std::ceil and cast to int
    return static_cast<int>(std::ceil(final_price));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate,
// and discount The returned number of days is rounded down (take the floor) to
// the next integer.
int days_in_budget(int budget, double hourly_rate, double discount) {
    // TODO: Implement a function that takes a budget, an hourly rate, and a
    // discount, and calculates how many complete days of work that covers.
    double daily_cost = daily_rate(hourly_rate);
    double discounted_daily_cost = apply_discount(daily_cost, discount);
    
    // Round down using std::floor and cast to int
    return static_cast<int>(std::floor(budget / discounted_daily_cost));
    
}
