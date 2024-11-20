#This file writes and executes querioes to add entries to a database.
#The program expects to read files with a certain structure
#First, the SQL table must be written in the 'tableName' 
#Second a txt file containing the data to be uploaded should be inputed in nthe "filename" variable
#In this file, each line should have a "number" (or address) followed by a lettert
#In my uses, the nunber refered to an apartment number and the letter was that aapartments response to a sales pitch


import mysql.connector

#global variables
tablename = ""
filename = ""

#create connection
link = mysql.connector.connect(user = '', password = '', host = '', database = '', auth_plugin='')

#Creating a cursor object
cursor = link.cursor()

#opens readable file
file = open(filename, "r")

#creates while loop that run until the end of the file
while file:

    #gets number from txt file
    number = file.read()

    #gets response letter from txt file
    response = file.read()

    #skips line
    file.readline()

    #writes it all into query
    query = '''INSERT INTO  ''' + tablename + '''( response, unitNumber) VALUES(''' + response + ''', ''' + number + ''');'''
    
    #executes query
    cursor.execute(query)

#closes file
file.close()
