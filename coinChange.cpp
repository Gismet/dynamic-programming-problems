#include <iostream>
#include <vector>

int total_calls; // total recursive calls

// This recursive solution is slow
int coinChange(std::vector<int> &coins, int amount)
{
    total_calls++;
    if (amount == 0) // if the given amount is zero, no coin is needed
        return 0;
    if (amount < 0) // if amount becomes negative, there is no way to make change
        return -1;

    int min = INT_MAX; // otherwise, check each coin and find the minimum number of coins needed to make change for the rest
    for (int coin : coins)
    {
        int change = coinChange(coins, amount - coin); // change needed to make for amount - coin after making a chage for 'coin'
        if (change != -1)                              // if the rest of the amount after making a change for 'coin' is not -1
            min = std::min(min, change) + 1;
    }
    return min == INT_MAX ? -1 : min; // if min remains the same, namely 'INT_MAX', return -1 otherwise return minimum number of coins
}

int coinChangeMemo(std::vector<int> &coins, int amount, std::vector<int> &memo)
{
    total_calls++;
    if (amount == 0)
        return 0;
    if (amount < 0)
        return -1;

    if (memo[amount] != -1)
        return memo[amount];

    int min = INT_MAX;
    for (int coin : coins)
    {
        int change = coinChangeMemo(coins, amount - coin, memo);
        if (change != -1)
            min = std::min(min, change + 1);
    }
    memo[amount] = min == INT_MAX ? -1 : min;
    return memo[amount];
}

int coinChangeDP(std::vector<int> &coins, int amount)
{
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
    {
        for (int j = 0; j < coins.size(); j++)
        {
            if (i - coins[j] >= 0)
                dp[i] = std::min(dp[i], 1 + dp[i - coins[j]]);
        }
    }
    return dp[amount] == amount + 1 ? -1 : dp[amount];
}

int main()
{
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;

    std::vector<int> memo(amount + 1, -1);
    total_calls = 0;
    std::cout << coinChange(coins, amount) << " in " << total_calls << " calls" << std::endl;
    total_calls = 0;
    std::cout << coinChangeMemo(coins, amount, memo) << " in " << total_calls << " calls" << std::endl;
    std::cout << coinChangeDP(coins, amount);

    return 0;
}