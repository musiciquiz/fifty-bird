from cs50 import get_int


# prompt input
card = get_int("Number: ")
# calculate checksum
# initiate global variables

counter_even = 10
counter_odd = 1
sum_even = 0
sum_odd = 0
# finding sum even numbers with counter i
i = 100
while True:
    x = int((card % i) / counter_even)
    counter_even *= 100
    x *= 2
    # what if double digit number?
    if x > 9:
        x = (x % 10) + 1
    sum_even += x
    i *= 100
    if i > 55999999999999999:
        break

# finding sum odd numbers with counter j
j = 10
while True:
    x = int((card % j) / counter_odd)
    counter_odd *= 100
    sum_odd += x
    j *= 100
    if j > 55999999999999999:
        break

checksum = sum_even + sum_odd

# check for card length and starting digits
# VISA - 13 digit and starts with 4
if (card >= 4000000000000 and card < 5000000000000 and checksum % 10 == 0):
    print("VISA")

# VISA - 16 digit and start with 4
elif (card >= 4000000000000000 and card < 5000000000000000 and checksum % 10 == 0):
    print("VISA")

# MASTERCARD 16 digit start 51,52,53,54,55
elif (card >= 5100000000000000 and card < 5600000000000000 and checksum % 10 == 0):
    print("MASTERCARD")

# AMEX 15 digit starts 34 or 37
elif (card >= 340000000000000 and card < 350000000000000 and checksum % 10 == 0):
    print("AMEX")

elif (card >= 370000000000000 and card < 380000000000000 and checksum % 10 == 0):
    print("AMEX")

else:
    print("INVALID")
