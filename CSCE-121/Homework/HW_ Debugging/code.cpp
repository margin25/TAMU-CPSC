int Product(int a, int b)
{
    if (a >= 0 && b > 0 && a > INT32_MAX / b)
    {
        throw std::overflow_error("overflow");
    }
    if ((a <= 0) && (b < 0) && (a < INT32_MAX / b))
    {
        throw std::overflow_error("overflow");
    }
    if ((a <= 0) && (b > 0) && (a < INT32_MIN / b))
    {
        throw std::overflow_error("overflow");
    }
    if ((a >= 0) && (b < 0) && (a > INT32_MIN / b))
    {
        throw std::overflow_error("overflow");
    }
    return a * b;
}

int Largest(int a, int b, int c)
{
    int d = a;

    if (b > d)
    {
        d = b;
    }
    if (c > d)
    {
        d = c;
    }
    return d;
}

bool SumIsEven(int a, int b)
{
    //debugging
    //code
    if ((a + b) % 2 == 1 || (a + b) % 2 == -1)
        return false;
    else
        return true;
}

int SumBetween(int low, int high)
{
    int value = 0;
    std::cout << low << std::endl;
    std::cout << high << std::endl;
    if (low > high)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (low == high)
    {
        return (low);
    }

    if (low == -(high))
        return 0;

    if (low < 0 && high > 0)
    {
        //This block converts to the same side of the number so that
        // we can actually do calculations w/o errors
        if (low < -(high))
            high = (-high) - 1;
        else
            low = (-low) + 1;
    }
    // after we flip the range (even if we don't) this block
    // if it is one number long it returns the number itself
    if (low == high)
        return low;

    //SUM(M, N) = (N - M + 1)(N + M) / 2
    //formula that computes the sum

    int temp = 0;
    //This block makes sure that the formula doesn't overflow
    //and throws an overflow_error warning statement if it does
    if ((high + low) % 2 == 0)
    {
        temp = (high + low) / 2;
        value = (high - low + 1) * temp;
        if ((value / temp) != (high - low + 1))
            throw std::overflow_error("multiplication overflow");
    }
    else
    {
        temp = (high - low + 1) / 2;
        value = temp * (high + low);
        if ((value / temp) != (high + low))
            throw std::overflow_error("multiplication overflow");
    }
    std::cout << value << std::endl;
    return value;
}

int BoxesNeeded(int apples)
{

    if (apples < 0)
        return 0;
    else if (apples % 20 != 0)
        return ((apples / 20) + 1);
    else
        return (apples / 20);
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total)
{
    if (A_total <= 0 || B_total <= 0)
    {
        throw std::invalid_argument("invalid argument");
    }
    if (A_correct < 0 || B_correct < 0)
    {
        throw std::invalid_argument("invalid argument");
    }

    if ((A_correct > A_total) || (B_correct > B_total))
    {
        throw std::invalid_argument("invalid argument");
    }
    return ((A_correct * 1.0) / (A_total) > (B_correct * 1.0) / (B_total));
}

bool GoodDinner(int pizzas, bool is_weekend)
{
    if ((!is_weekend) && (pizzas >= 10 && pizzas <= 20))
    {
        return true;
    }
    else if (is_weekend && pizzas >= 10)
    {
        return true;
    }
    else
        return false;
}