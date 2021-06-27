import re
import string



def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

# double a number value to be called by main program
def DoubleValue(v):
    return v * 2

# multiplication table function
def MultiplicationTable(v):
    for i in range(1,11):
        print("{0} * {1} = {2}".format(v,i,(v * i)))
    # incorporated the necessary return value with some humor will figure out a way to bypass later
    print("")
    print ("The table above is brought to you by the number:")
    return v



def purchaseList():

    # This function will read a file
    # It will count the total amount of each product
    

    ticket = open("project_three_input_file.txt") #creates object that opens text file
    products = ticket.read().split() #creates object that holds each line info from ticket object
    
    individualProduct = sorted(set(products))
    print("Items Purchased")
    for word in individualProduct:

        print("------------------------------------")
        print(products.count(word), ":",  word)
    

    ticket.close() #closes ticket object to prevent memory issues

    
# will search through text file to count the total occurance of item
def freqItem(v):
   
    # object opens text file 
    ticket = open("project_three_input_file.txt")
    products = ticket.read().split() #creates object that holds each line info from ticket object
    individualProduct = sorted(set(products)) #sorts the items
    ticket.close() #closes ticket object to prevent memory issues


    total = 0 #number to be sent back to C++
    totalInventory = 0 #counts amount of times loop iterates
    totalInventoryCount = 0 # place holder total inventory in document file

    for word in individualProduct: # get total amount of items in list 
        totalInventoryCount += 1

    for word in individualProduct: #finds the element that is requested string from user
        temp_String = word
        totalInventory += 1
        if (temp_String == v):
            total = products.count(word)
            totalInventory -= 1 #  used to determine if user input actually in file
        if (temp_String != v and totalInventory == totalInventoryCount):
            return -1 # used determined that item from user input was not present in file

    
    
    return total

def Histogram():
    print("Histogram of Items purchased")
    print("------------------------------------")
    print("")
    # takes information from text file
    # counts product and sorts/counts items
    # Takes the sorted and counted items and writes to a dat file

    ticket = open("project_three_input_file.txt")
    data = open("frequency.dat", "w")
    #creates object that holds each line info from ticket object and sorts
    products = ticket.read().split() 
    individualProduct = sorted(set(products))

    
    #writes the data to the .dat file
    for word in individualProduct:
        data.write(word)
        data.write(" ")
        #write to .dat file using string
        data.write(str(products.count(word))) 
        data.write("\n")
    
    data.close() 
    # read .dat file
    histData = open("frequency.dat", "r") 
    productData = histData.readlines() 


    #temp variables used for loops
    tempFreq = 0
    tempProduct = ""

    #reads and prepares data from .dat file for histogram
    for line in productData:
        tempInt = 0
        #seperates product name and frequency
        tempString = line.split() 
        for word in tempString:
            tempInt += 1
            if (tempInt == 1):
                tempProduct = word 
                print(tempProduct, end = " ")
            if (tempInt == 2):
                tempFreq = int(word) #frequency of product
        
        
        #creates Histogram 
        for i in range(tempFreq):
            print("+", end = "")
        print("\n------------------------------------")
        
        
        