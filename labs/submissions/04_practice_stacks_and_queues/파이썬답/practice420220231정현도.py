import sys


#input string is one line without subtracted input.txt's 2char (op,spacebar)
#return boolean type
# [::-1] is reverse string order 
def isPalindrome(string):
  if string == string[::-1]:  #O(n)  
    return True               
  
  else:
    return False              



if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == 'P':
        if len(words) != 2:
          raise Exception("PALINDROME: invalid input")
        ret = "T" if isPalindrome(words[1]) else "F"
        outFile.write(ret+"\n")
      elif op == 'B':
        if len(words) != 2:
          raise Exception("BALANCE: invalid input")
        ret = "T" if balance(words[1]) else "F"
        outFile.write(ret+"\n")
      else:
        raise Exception("Undefined operator")

        
