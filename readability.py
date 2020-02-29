from cs50 import get_string

# Get input from user
text = get_string("Text: ")

total_letters = 0
total_words = 1  # initialise to 1 as first character is also first word
total_sent = 0

for char in text:
    # is it a letter
    if(char.isalpha()):
        total_letters += 1
    # is it a blank
    if(char.isspace()):
        total_words += 1
    # is it end of sentence
    if(char == "." or char == "?" or char == "!"):
        total_sent += 1

L = total_letters / total_words * 100

S = total_sent / total_words * 100

index = .0588 * L - 0.296 * S - 15.8

if(index < 1):
    print("Before Grade 1")

elif(index >= 16):
    print("Grade 16+")

else:
    print(f"Grade {round(index)}")
