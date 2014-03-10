/* Simple C program that connects to MySQL Database server*/
// Must be compiled as follows:
// gcc mysql_test.c -o mysql_test -std=c99  `mysql_config --cflags --libs`

#include <mysql.h>
#include <stdio.h>

main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *first_f = (char *)malloc(sizeof(char)*(100 + 1));
   char *last_f = (char *)malloc(sizeof(char)*(100 + 1));

   char *server = "localhost";
   char *user = "root";
   char *password = "Anduril!12"; /* set me first */
   char *database = "menangerie";

   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) 
   {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   printf("Enter the first actor's first name: ");
   scanf("%100s %100s", first_f, first_l);
   printf("%s %s", first_f, first_l);

   /* send SQL query */
   if (mysql_query(conn, "SHOW TABLES")) 
   {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

   /* output table name */
   printf("MySQL Tables in mysql database:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);

   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
}
