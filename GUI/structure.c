typedef struct {
	GtkWidget *window;
	GtkWidget *button1;
	GtkWidget *button2;
    GtkListStore *listStore;
    GtkTreeIter   iter;
} Form1;

typedef struct {
	GtkWidget *window;
	GtkWidget *label1;
	GtkWidget *buttonConvert;
	GtkWidget *button3;
	GtkWidget *combobox1;
	GtkWidget *combobox2;
	GtkWidget *textBox1;
	GtkWidget *checkBox1;
	
	GtkWidget *buttonNum[12];
	GtkWidget *buttonOp[4];
	GtkWidget *equalOp;
} Form2;

typedef struct {
	GtkWidget *window;
	GtkWidget *label1;
	GtkWidget *comboBox1;
	GtkWidget *comboBox2;
	GtkWidget *comboBox3;
	GtkWidget *comboBox4;
	GtkWidget *comboBox5;
	GtkWidget *comboBox6;
	GtkWidget *button1;
	GtkWidget *button2;
} Form3;

Form1 form1;
Form2 form2;
Form3 form3;

char line[100];
char clearScreen = 1;
double val1 = 0;
double val2 = 0;
char operator = 0;
char *fullname[] = {" ", "US Dollar", "Argentine Peso", "Australian Dollar", "Bahraini Dinar", "Botswana Pula", "Brazilian Real", "Bruneian Dollar", "Bulgarian Lev", "Canadian Dollar", "Chilean Peso", "Chinese Yuan Renminbi", "Colombian Peso", "Croatian Kuna", "Czech Koruna", "Danish Krone", "Euro", "Hong Kong Dollar", 		"Hungarian Forint", "Icelandic Krona", "Indian Rupee", "Indonesian Rupiah", "Iranian Rial", "Israeli Shekel", "Japanese Yen", 			"Kazakhstani Tenge", "South Korean Won", "Kuwaiti Dinar", "Latvian Lat", "Libyan Dinar", "Lithuanian Litas", "Malaysian Ringgit", 			"Mauritian Rupee","Mexican Peso", "Nepalese Rupee", "New Zealand Dollar", "Norwegian Krone", "Omani Rial", "Pakistani Rupee", 			"Philippine Peso", "Polish Zloty", "Qatari Riyal", "Romanian New Leu", "Russian Ruble", "Saudi Arabian Riyal", "Singapore Dollar", 			"South African Rand", "Sri Lankan Rupee", "Swedish Krona", "Swiss Franc", "Taiwan New Dollar", "Thai Baht", "Trinidadian Dollar", 			"Turkish Lira", "Emirati Dirham", "British Pound", "Venezuelan Bolivar" };
char *nepmonth[] = { "Baishakh", "Jestha", "Aasar", "Shrawan", "Bhadra", "Ashoj", "Kartik", "Mangsir", "Poush", "Magh", "Falgun", "Chaitra" };
char *engmonth[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

void form2Execute(char *);

