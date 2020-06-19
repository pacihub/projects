from cs50 import get_string

s = get_string("Text: ")

word_count = 0
sentence = 0
letter = 0

for i in range(len(s)):
    if((s[i] == ' ' and s[i+1] != ' ') or (i == 0 and s[i+1] != ' ')):
        word_count += 1

    if(s[i] == '.' or s[i] =='!' or s[i] == '?'):
            sentence += 1
            

    if s[i].isalpha():
            letter += 1
            


L = float((100/word_count) * letter)
S = float((100/word_count) * sentence)


index = int(round(0.0588 * L - 0.296 * S - 15.8))
        
if index < 1:
        print("Before Grade 1")
        
elif index >= 16:
        print(" Grade 16+")
        
else:
    print(f"Grade {index}")