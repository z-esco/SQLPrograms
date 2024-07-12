import mysql.connector

#global variables
tablename = "vox"
filename = "vox.txt"

#create connection
link = mysql.connector.connect(user = 'Zesco4$', password = 'JkwhaDGU4$&9', host = 'KickassCalculator', database = 'clientList', auth_plugin='mysql_native_password')

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