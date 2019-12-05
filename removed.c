{
    if (equation[i] <= '9' && equation[i] >= '0')
        operation[i - space][0] = equation[i] - '0';
    else if (equation[i] == '+')
        operation[i - space][1] = 1;
    else if (equation[i] == '-')
        operation[i - space][1] = 0;
    else if (equation[i] == '*')
        operation[i - space][1] = 2;
    else if (equation[i] == ' ')
        space++;
}