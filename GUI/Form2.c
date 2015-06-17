
static gboolean DeleteEvent1 (GtkWidget *window, GdkEvent *event, gpointer data) {
	gtk_widget_hide(GTK_WIDGET(form2.window));
	gtk_widget_show(GTK_WIDGET(form1.window));
	
	return TRUE;
}

static void button3Converter (GtkWidget *window, gpointer data) {
	char *ptr1, *ptr2;
	int i , from, to;
	char command[255] = "";
	const char *amount;
	int check;
	
	ptr1 = (char *)gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form2.combobox1));
	ptr2 = (char *)gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form2.combobox2));
	amount = gtk_entry_get_text(GTK_ENTRY(form2.textBox1));
	
	for (i = 0; i <= 56; i++) {
		if (!strcmp(ptr1, fullname[i])){
			from = i;
		}
		if (!strcmp(ptr2, fullname[i])) {
			to = i;
		}
	}

	check = (int)gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(form2.checkBox1));
	
	if (check){
		sprintf (command, "currencyconverter %d %d %s \n", from, to, amount);
	} else {
		sprintf (command, "currencyconverter %d %d %s -nd \n", from, to, amount);
	}
	
	form2Execute(command);
	gtk_label_set_text (GTK_LABEL(form2.label1), line);
	
}	
		
static void numberClicked (GtkWidget *window, gpointer data) {
	char newText[100];
	const char *temp;
	if (!(strcmp("<--",gtk_button_get_label(GTK_BUTTON(data))))){
		int length;
		temp = gtk_entry_get_text(GTK_ENTRY(form2.textBox1));
		length = strlen(temp);
		if (length != 0){
			if (length == 1){
				gtk_entry_set_text(GTK_ENTRY(form2.textBox1), " ");
			} else {
				strcpy(newText, temp);
				newText[--length] = '\0';
				printf("%s\n", newText); 
				gtk_entry_set_text(GTK_ENTRY(form2.textBox1), newText);
			}
		}
		return;
	}
	
	if (clearScreen){
		gtk_entry_set_text(GTK_ENTRY(form2.textBox1), gtk_button_get_label(GTK_BUTTON(data)));
		clearScreen = 0;
	} else {
		temp = gtk_entry_get_text(GTK_ENTRY(form2.textBox1));
		sprintf (newText, "%s%s", temp, gtk_button_get_label(GTK_BUTTON(data)));
		gtk_entry_set_text(GTK_ENTRY(form2.textBox1), newText);
	}
	
}

double giveResult(double value1, double value2, char operator){
	switch(operator){
		case 1:
			return value1 + value2;
			break;
		
		case 2:
			return value1 - value2;
			break;
			
		case 3:
			return value1 * value2;
			break;
			
		case 4:
			return value1 / value2;
			break;
			
		default:
			return -1;
	}
}

char *removeTrailingZeros(double value){
    char dummy[100] = "";
    int counter;
    char *result;
    sprintf (dummy, "%.12f", value);
    
    for (counter=strlen(dummy)-1; counter>=0; counter--){
        if (dummy[counter] != '0' && dummy[counter] != '.'){
            dummy[counter+1] = '\0';
            break;
        } else if (dummy[counter] == '.'){
            dummy[counter] = '\0';
        }
    }
    result = malloc(counter+2);
    result = strcpy (result, dummy);
    return result;
}

static void opClicked (GtkWidget *window, gpointer data) {
    int dummy;
    char *result; 

	if (operator == 0 || clearScreen == 1){
		val1 = atof(gtk_entry_get_text(GTK_ENTRY(form2.textBox1)));
	} else {
		val2 = atof(gtk_entry_get_text(GTK_ENTRY(form2.textBox1)));
		val1 = giveResult(val1, val2, operator);
 
        result = removeTrailingZeros(val1);       
		gtk_entry_set_text(GTK_ENTRY(form2.textBox1), result);
        free (result);
	}
	
	if (strcmp(gtk_button_get_label(GTK_BUTTON(data)), "=")) {
		if (!strcmp(gtk_button_get_label(GTK_BUTTON(data)), "+")){
			operator = 1;
		} else if (!strcmp(gtk_button_get_label(GTK_BUTTON(data)), "-")){
			operator = 2;
		} else if (!strcmp(gtk_button_get_label(GTK_BUTTON(data)), "x")){
			operator = 3;
		} else if (!strcmp(gtk_button_get_label(GTK_BUTTON(data)), "/")){
			operator = 4;
		}
	} else {
		val1 = 0;
		operator = 0;
	}
	clearScreen = 1;
}
	
void form2SignalsConnector() {
	int i;
	
	g_signal_connect (G_OBJECT (form2.window), "delete_event", G_CALLBACK (DeleteEvent1), NULL);
	g_signal_connect (G_OBJECT (form2.buttonConvert), "clicked", G_CALLBACK (button3Converter), form2.button3);
	
	for (i = 0; i <= 11; i++) {
		g_signal_connect (G_OBJECT (form2.buttonNum[i]), "clicked", G_CALLBACK (numberClicked), form2.buttonNum[i]);	
	}
	
	for (i = 0; i <= 3; i++) {
		g_signal_connect (G_OBJECT (form2.buttonOp[i]), "clicked", G_CALLBACK (opClicked), form2.buttonOp[i]);
	}
		
	g_signal_connect (G_OBJECT (form2.equalOp), "clicked", G_CALLBACK (opClicked), form2.equalOp);	
}


void form2UiDesign(GtkBuilder *builder) {
	int i;

	form2.window = GTK_WIDGET (gtk_builder_get_object (builder, "window2"));
	form2.label1 = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));
	form2.buttonConvert = GTK_WIDGET (gtk_builder_get_object (builder, "button3"));
	form2.combobox1 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext1"));
	form2.combobox2 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext8"));
	form2.textBox1 = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
	form2.checkBox1 = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton1"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(form2.checkBox1), TRUE); 
	
	form2.buttonNum[0] = GTK_WIDGET (gtk_builder_get_object (builder, "button13"));
	form2.buttonNum[1] = GTK_WIDGET (gtk_builder_get_object (builder, "button10"));
	form2.buttonNum[2] = GTK_WIDGET (gtk_builder_get_object (builder, "button11"));
	form2.buttonNum[3] = GTK_WIDGET (gtk_builder_get_object (builder, "button12"));
	form2.buttonNum[4] = GTK_WIDGET (gtk_builder_get_object (builder, "button7"));
	form2.buttonNum[5] = GTK_WIDGET (gtk_builder_get_object (builder, "button8"));
	form2.buttonNum[6] = GTK_WIDGET (gtk_builder_get_object (builder, "button9"));
	form2.buttonNum[7] = GTK_WIDGET (gtk_builder_get_object (builder, "button4"));
	form2.buttonNum[8] = GTK_WIDGET (gtk_builder_get_object (builder, "button5"));
	form2.buttonNum[9] = GTK_WIDGET (gtk_builder_get_object (builder, "button6"));
	form2.buttonNum[10] = GTK_WIDGET (gtk_builder_get_object (builder, "button14"));
	form2.buttonNum[11] = GTK_WIDGET (gtk_builder_get_object (builder, "button21"));
	
	form2.buttonOp[0] = GTK_WIDGET (gtk_builder_get_object (builder, "button19"));
	form2.buttonOp[1] = GTK_WIDGET (gtk_builder_get_object (builder, "button18"));
	form2.buttonOp[2] = GTK_WIDGET (gtk_builder_get_object (builder, "button17"));
	form2.buttonOp[3] = GTK_WIDGET (gtk_builder_get_object (builder, "button16"));
	
	form2.equalOp = GTK_WIDGET (gtk_builder_get_object (builder, "button20"));
	gtk_entry_set_alignment (GTK_ENTRY(form2.textBox1), 1);

	for (i = 1; i <= 56; i++) {
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(form2.combobox1), NULL,  fullname[i]);
		gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(form2.combobox2), NULL,  fullname[i]);
	}	
	
	gtk_combo_box_set_active (GTK_COMBO_BOX(form2.combobox1), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form2.combobox2), 33);
}

void form2Execute(char *command) {
	FILE *file;
	
	file = popen(command, "r");
	if (file == NULL) {
		printf("CUI application not found, try running after reinstalling program\n");
		return;
	}
	
	getlines(file);
}

int getlines(FILE *ptr) {
	int i;
	char s[2];

	for (i = 0;(fgets(s, sizeof(s), ptr) != NULL) && s[0] != '\n'; i++) {
			line[i] = s[0];			
	}
	line[i] = '\0';
	return i;
}		 

