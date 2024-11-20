#In this program, go to the line that begins with link and fill in the appropriate info
#This program will attempt to connnect to a SQL database from your local system
#The program will return proper error messages based on the issue to help solve it

import mysql.connector
from mysql.connector import errorcode

try:
  link = mysql.connector.connect(user = '', password = '', host = '' database = '', auth_plugin='')

except mysql.connector.Error as err:
  if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
    print("Something is wrong with your user name or password")
  elif err.errno == errorcode.ER_BAD_DB_ERROR:
    print("Database does not exist")
  else:
    print(err)
else:
    link.close()
