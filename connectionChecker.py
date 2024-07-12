import mysql.connector
from mysql.connector import errorcode





try:
  link = mysql.connector.connect(user = 'Zesco4$', password = 'JkwhaDGU4$&9', host = 'KickassCalculator', database = 'clientList', auth_plugin='mysql_native_password')

except mysql.connector.Error as err:
  if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
    print("Something is wrong with your user name or password")
  elif err.errno == errorcode.ER_BAD_DB_ERROR:
    print("Database does not exist")
  else:
    print(err)
else:
    link.close()