#include "ex6q1.h"


#define LEN 200000000


// This function should be pure recursion - no dynamic programming allowed

uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {
    EXP_MOD_1_CALL_COUNT++;

    if(exp == 0) return 1;
    if(exp == 1) return base % modulo;

    uint32_t half_exp = exp / 2;
    uint32_t remaining_exp = exp - half_exp;

    uint32_t part_1_calls = exp_mod_1(base, half_exp, modulo);
    uint32_t part_2_calls = exp_mod_1(base, remaining_exp, modulo);

    return (uint32_t)(((uint64_t)part_1_calls * (uint64_t)part_2_calls) % modulo);
}



// This function should store the values of previous calls to exp_mod_2 in an

// array and use them for later calculations.

uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {
    EXP_MOD_2_CALL_COUNT++;

    static uint32_t memo[LEN];

    if(exp == 0) return 1;
    if(exp == 1) return base % modulo;

    // If the result is already in memo array, use it
    if(memo[exp] != 0) return memo[exp];

    uint32_t half_exp = exp / 2;
    uint32_t remaining_exp = exp - half_exp;

    uint32_t part_1_calls = exp_mod_2(base, half_exp, modulo);
    uint32_t part_2_calls = exp_mod_2(base, remaining_exp, modulo);

    // Store result in memo array and return
    memo[exp] = (uint32_t)(((uint64_t)part_1_calls * (uint64_t)part_2_calls) % modulo);
    return memo[exp];
}



int main(void) {

    uint32_t base, exp, modulo;


    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {

        return 1;

    }

    

    uint32_t mod_1 = exp_mod_1(base, exp, modulo);

    uint32_t mod_2 = exp_mod_2(base, exp, modulo);


    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);

    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);

    fprintf(stdout, "%d == %d\n", mod_1, mod_2);

}