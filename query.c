#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con) {
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc, char *argv[]) {
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		exit(1);
	}
	if (mysql_real_connect(con, "localhost", "root", "your_password",
						   "your_database", 0, NULL, 0) == NULL) {
		finish_with_error(con);
	}
	if (mysql_query(con, "SELECT match.match_identifier, match.finish_time, match.duration, "
					"p.username AS winner "
					"FROM match "
					"JOIN player_match ON match.match_id = player_match.match_id "
					"JOIN player ON match.winner_id = player.player_id "
					"WHERE player_match.player_id = 1")) {
		finish_with_error(con);
	}
	MYSQL_RES *result = mysql_store_result(con);
	
	if (result == NULL) {
		finish_with_error(con);
	}
	
	int num_fields = mysql_num_fields(result);
	
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	while((field = mysql_fetch_field(result))) {
		printf("%s\t", field->name);
	}
	printf("\n");
	
	// Print each row of the result
	while ((row = mysql_fetch_row(result))) {
		for(int i = 0; i < num_fields; i++) {
			printf("%s\t", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	// Clean up
	mysql_free_result(result);
	mysql_close(con);
	
	exit(0);
}

