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
