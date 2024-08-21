/**************************************************
 * Title: DatabaseSystem - Project 2
 * Summary: A Real-Estate Office
 *  |Date              |Author
	|2024-06-07        |Dosol Kim
**************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "ehthfsql12#";

using namespace std;

#define MAX_LEN			13000

int main(void) {
	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	// open CRUD file.
	FILE* fp = fopen("CRUD.txt", "rt");
	if (fp == NULL) {
		printf("file does not exist!\n");
		return 0;
	}
	char line[MAX_LEN];

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	// the first NULL can be replaced to an existing db instance.
	connection = mysql_real_connect(&conn, host, user, pw, NULL, 3306, (const char*)NULL, 0);
	if (connection == NULL) {
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	else {
		printf("Connection Succeed\n\n");

		while (fgets(line, sizeof(line), fp) != NULL) {
			if (!strcmp(line, "$$$\n"))      // read lines from CRUD file, '$$$' separates CREATE / DELETE parts.
				break;
			mysql_query(connection, line);
		}

		if (mysql_select_db(&conn, "project")) {
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		
		int select;
		// start
		while (1) {
			printf("\n---------- SELECT QUERY TYPES ----------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n\n");
			printf("Enter the type: ");
			scanf("%d", &select);
			printf("\n");

			switch (select) {
				case 0: {
					printf("\n---------- QUIT ----------\n");
					// comment out if you want to persist example db instance.
					while (fgets(line, sizeof(line), fp) != NULL)
						mysql_query(connection, line); // these are DELETEs & DROPs.
					mysql_close(connection);
					return 0;
					break;
				}
				case 1: {
					while (1) {
						printf("---------- TYPE 1 ----------\n");
						printf("** Find address of homes for sale in the district “Mapo”. **\n");

						char query[] = "SELECT property_id, address FROM property WHERE district_id = 'Mapo-gu' AND status = 'on_the_market'";

						int state = 0;
						state = mysql_query(connection, query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("[%s] %s, Mapo-gu, Seoul\n", sql_row[0], sql_row[1]);
							}
							mysql_free_result(sql_result);
						}

						while (1) {
							int sub;
							printf("\n---------- Subtypes in TYPE 1 ----------\n");
							printf("\t1. TYPE 1-1\n");
							printf("\t0. QUIT\n\n");
							printf("Enter the subtype: ");
							scanf("%d", &sub);
							if (sub == 0) break;
							else if (sub == 1) {
								printf("\n---------- TYPE 1-1 ----------\n");
								printf("** Then find the costing between ￦1,000,000,000 and ￦1,500,000,000. **\n");
								
								char query[] = "SELECT property_id, address, price FROM property WHERE district_id = 'Mapo-gu' AND status = 'on_the_market' AND price BETWEEN 1000000000 AND 1500000000";
								
								int state = 0;
								state = mysql_query(connection, query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("[%s] %s, Mapo-gu, Seoul | price: %s\n", sql_row[0], sql_row[1], sql_row[2]);
									}
									mysql_free_result(sql_result);
								}
								continue;
							}
							else {
								printf("Wrong choice.\n");
								continue;
							}
						}
						break;
					}
					break;
				}
				case 2: {
					while (1) {
						printf("---------- TYPE 2 ----------\n");
						printf("** Find the address of homes for sale in the 8th school district. **\n");

						char query[] = "SELECT property.property_id, property.address, property.district_id FROM property JOIN district ON property.district_id = district.district_id WHERE district.school_district = 8 AND property.status = 'on_the_market'";
						
						int state = 0;
						state = mysql_query(connection, query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("[%s] %s, %s, Seoul\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}

						while (1) {
							int sub;
							printf("\n---------- Subtypes in TYPE 2 ----------\n");
							printf("\t1. TYPE 2-1\n");
							printf("\t0. QUIT\n\n");
							printf("Enter the subtype: ");
							scanf("%d", &sub);
							printf("\n");
							if (sub == 0) break;
							else if (sub == 1) {
								printf("\n---------- TYPE 2-1 ----------\n");
								printf("** Then find properties with 4 or more bedrooms and 2 bathrooms. **\n");
								
								char query[] = "SELECT property.property_id, property.address, property.district_id, property.number_of_bedrooms, property.number_of_bathrooms FROM property JOIN district ON property.district_id = district.district_id WHERE district.school_district = 8 AND property.status = 'on_the_market' AND property.number_of_bedrooms >= 4 AND property.number_of_bathrooms >= 2";
								
								int state = 0;
								state = mysql_query(connection, query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("[%s] %s, %s, Seoul\n", sql_row[0], sql_row[1], sql_row[2]);
										printf("        number_of_bedrooms: %s, number_of_bathrooms: %s\n", sql_row[3], sql_row[4]);
									}
									mysql_free_result(sql_result);
								}
								continue;
							}
							else {
								printf("Wrong choice.\n");
								continue;
							}
						}
						break;
					}
					break;
				}
				case 3: {
					while (1) {
						printf("---------- TYPE 3 ----------\n");
						printf("** Find the name of the agent who has sold the most properties in the year 2022 by total won value. **\n");

						char query[] = "SELECT agent.agent_id, agent.name, SUM(sale.sale_price) FROM sale JOIN agent ON sale.selling_agent_id = agent.agent_id WHERE YEAR(sale_date) = 2022 GROUP BY agent.agent_id ORDER BY SUM(sale_price) DESC LIMIT 1";
						
						int state = 0;
						state = mysql_query(connection, query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("[%s] %s | total won value: \\%s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						printf("\n");

						while (1) {
							int sub;
							printf("\n---------- Subtypes in TYPE 3 ----------\n");
							printf("\t1. TYPE 3-1\n");
							printf("\t2. TYPE 3-2\n");
							printf("\t0. QUIT\n\n");
							printf("Enter the subtype: ");
							scanf("%d", &sub);
							printf("\n");
							if (sub == 0) break;
							else if (sub == 1) {
								printf("\n---------- TYPE 3-1 ----------\n");
								printf("** Then find the top k agents in the year 2023 by total won value. **\n");
								char k[5] = {};
								printf("Enter the k(<=10): ");
								scanf("%s", &k);
								if (k == 0) break;

								char query[300] = "SELECT agent.agent_id, agent.name, SUM(sale.sale_price) AS total_sales FROM sale JOIN agent ON sale.selling_agent_id = agent.agent_id WHERE YEAR(sale.sale_date) = 2023 GROUP BY agent.agent_id, agent.name ORDER BY total_sales DESC LIMIT ";
								strcat(query, k);

								int state = 0;
								state = mysql_query(connection, query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										printf("[%s] %13s | total won value: \\%s\n", sql_row[0], sql_row[1], sql_row[2]);
									}
									mysql_free_result(sql_result);
								}
								printf("\n");
								continue;
							}
							else if (sub == 2) {
								printf("\n---------- TYPE 3-2 ----------\n");
								printf("** And then find the bottom 10%% agents in the year 2021 by total won value. **\n");

								// First query to count the number of agents in bottom 10%
								char count_query[] = "SELECT CEIL(COUNT(DISTINCT selling_agent_id) * 0.1) FROM sale WHERE YEAR(sale_date) = 2021";
								int count = 0;

								int state = mysql_query(connection, count_query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
										count = atoi(sql_row[0]);
									}
									mysql_free_result(sql_result);
								}

								if (count > 0) {
									// Second query to get the bottom 10% agents by total won value
									char query[512];
									snprintf(query, sizeof(query),
										"SELECT agent.agent_id, agent.name, SUM(sale.sale_price) AS total_sales FROM sale JOIN agent ON sale.selling_agent_id = agent.agent_id WHERE YEAR(sale.sale_date) = 2021 GROUP BY agent.agent_id, agent.name ORDER BY total_sales ASC LIMIT %d", count);

									state = mysql_query(connection, query);
									if (state == 0) {
										sql_result = mysql_store_result(connection);
										while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
											printf("[%s] %s | total won value: \\%s\n", sql_row[0], sql_row[1], sql_row[2]);
										}
										mysql_free_result(sql_result);
									}
								}
								else {
									printf("No agents found for the bottom 10%% criteria.\n");
								}
								printf("\n");
								continue;
							}
							else {
								printf("Wrong choice.\n");
								continue;
							}
						}
						break;
					}
					break;
				}
				case 4: {
					while (1) {
						printf("---------- TYPE 4 ----------\n");
						printf("** For each agent, compute the average selling price of properties sold in 2022, and the average time the property was on the market. **\n");

						char query[] = "SELECT s.selling_agent_id, AVG(s.sale_price) AS avg_selling_price_2022, AVG(TIMESTAMPDIFF(DAY, p.listing_date, s.sale_date)) AS avg_time_on_market_days_2022 FROM sale s JOIN property p ON s.property_id = p.property_id WHERE YEAR(s.sale_date) = 2022 GROUP BY s.selling_agent_id";
						
						int state = 0;
						state = mysql_query(connection, query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								double price = atof(sql_row[1]);
								double time = atof(sql_row[2]);
								printf("[%s] avg price: \\%10.0f | avg time: %4.1f days\n", sql_row[0], price, time);
							}
							mysql_free_result(sql_result);
						}
						printf("\n");

						while (1) {
							int sub;
							printf("\n---------- Subtypes in TYPE 4 ----------\n");
							printf("\t1. TYPE 4-1\n");
							printf("\t2. TYPE 4-2\n");
							printf("\t0. QUIT\n\n");
							printf(": ");
							scanf("%d", &sub);
							if (sub == 0) break;
							else if (sub == 1) {
								printf("\n---------- TYPE 4-1 ----------\n");
								printf("** Then compute the maximum selling price of properties sold in 2023 for each agent. **\n");

								char query[] = "SELECT s.selling_agent_id, MAX(s.sale_price) AS max_selling_price_2023 FROM sale s WHERE YEAR(s.sale_date) = 2023 GROUP BY s.selling_agent_id";
								int state = 0;
								state = mysql_query(connection, query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										double price = atof(sql_row[1]);
										printf("[%s] max price: \\%10.0f\n", sql_row[0], price);
									}
									mysql_free_result(sql_result);
								}
								printf("\n");
								continue;
							}
							else if (sub == 2) {
								printf("\n---------- TYPE 4-2 ----------\n");
								printf("** And then compute the longest time the property was on the market for each agent. **\n");

								char query[] = "SELECT s.selling_agent_id, MAX(TIMESTAMPDIFF(DAY, p.listing_date, s.sale_date)) AS longest_time_on_market_days FROM sale s JOIN property p ON s.property_id = p.property_id GROUP BY s.selling_agent_id";

								int state = 0;
								state = mysql_query(connection, query);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
									{
										double time = atof(sql_row[1]);
										printf("[%s] longest time: %4.1f days\n", sql_row[0], time);
									}
									mysql_free_result(sql_result);
								}
								printf("\n");
								continue;
							}
							else {
								printf("Wrong choice.\n");
								continue;
							}
						}
						break;
					}
					break;
				}
				case 5: {
					printf("---------- TYPE 5 ----------\n");
					printf("** Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s), respectively, from the database. **\n");
					
					char query[] = "SELECT property.type, photo.type, photo.file_path, photo.property_id, property.price FROM photo JOIN property ON photo.property_id = property.property_id WHERE property.type IN ('studio', 'one_bedroom', 'multi_bedroom', 'detached_house') AND property.price = (SELECT MAX(p2.price) FROM property p2 WHERE p2.type = property.type)";
					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("[%s] %s file path: %s (%s, price: %s)\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n");
					break;
				}
				case 6: {
					printf("---------- TYPE 6 ----------\n");
					printf("** Record the sale of a property that had been listed as being available. This entails storing the sales price,the buyer, the selling agent, the buyer’s agent(if any), and the date. **\n");

					char sale_id[20], property_id[20], buyer_id[20], selling_agent_id[20], buyers_agent_id[20];
					int sale_price;
					char sale_date[20];

					printf("\nEnter Sale ID(>=S0051): ");
					scanf("%s", sale_id);
					printf("Enter Property ID(P0001-P0060): ");
					scanf("%s", property_id);
					printf("Enter Buyer ID(BUY0001-BUY0010): ");
					scanf("%s", buyer_id);
					printf("Enter Selling Agent ID(AGT0001-AGT0010): ");
					scanf("%s", selling_agent_id);
					printf("Enter Buyer's Agent ID(AGT0001-AGT0010) or NULL if none: ");
					scanf("%s", buyers_agent_id);
					printf("Enter Sale Price: ");
					scanf("%d", &sale_price);
					printf("Enter Sale Date (YYYY-MM-DD): ");
					scanf("%s", sale_date);
					printf("\n");

					char query[1024];
					if (strcmp(buyers_agent_id, "NULL") == 0) {
						snprintf(query, sizeof(query), "INSERT INTO sale (sale_id, sale_price, sale_date, property_id, buyer_id, selling_agent_id, buyers_agent_id) VALUES ('%s', %d, '%s', '%s', '%s', '%s', NULL)",
							sale_id, sale_price, sale_date, property_id, buyer_id, selling_agent_id);
					}
					else {
						snprintf(query, sizeof(query), "INSERT INTO sale (sale_id, sale_price, sale_date, property_id, buyer_id, selling_agent_id, buyers_agent_id) VALUES ('%s', %d, '%s', '%s', '%s', '%s', '%s')",
							sale_id, sale_price, sale_date, property_id, buyer_id, selling_agent_id, buyers_agent_id);
					}

					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0) {
						printf("Sale record added successfully.\n");
					}
					else {
						printf("Failed to add sale record: %s\n", mysql_error(connection));
					}
					printf("\n");

					char query2[100];
					snprintf(query2, sizeof(query), "SELECT * FROM sale WHERE sale_id = '%s'", sale_id);
					
					int state2 = 0;
					state = mysql_query(connection, query2);
					if (state2 == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s | %s | %s | %s | %s | %s | %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n");

					break;
				}
				case 7: {
					printf("---------- TYPE 7 ----------\n");
					printf("** Add a new agent to the database. **\n");

					char agent_id[20], name[20], phone_number[20], hire_date[20];

					printf("\nEnter Agent ID (>=AGT0011): ");
					scanf("%s", agent_id);
					getchar();

					printf("Enter Name: ");
					fgets(name, sizeof(name), stdin);
					name[strcspn(name, "\n")] = '\0';

					printf("Enter Phone Number: ");
					scanf("%s", phone_number);
					getchar();

					printf("Enter Hire Date (YYYY-MM-DD): ");
					scanf("%s", hire_date);
					getchar();

					printf("\n");

					char query[512];
					snprintf(query, sizeof(query), "INSERT INTO agent (agent_id, name, phone_number, hire_date) VALUES ('%s', '%s', '%s', '%s')",
						agent_id, name, phone_number, hire_date);

					int state = 0;
					state = mysql_query(connection, query);
					if (state == 0) {
						printf("Agent added successfully.\n");
					}
					else {
						printf("Failed to add agent: %s\n", mysql_error(connection));
					}
					printf("\n");

					char query2[100];
					snprintf(query2, sizeof(query), "SELECT * FROM agent WHERE agent_id = '%s'", agent_id);

					int state2 = 0;
					state = mysql_query(connection, query2);
					if (state2 == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s | %s | %s | %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n");

					break;
				}
				default: {
					printf("Wrong choice.\n");
					continue;
				}
			}
		}
	}
	return 0;
}