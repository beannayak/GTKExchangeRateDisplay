
static gboolean DeleteEvent2 (GtkWidget *window, GdkEvent *event, gpointer data) {
	gtk_widget_hide(GTK_WIDGET(form3.window));
	gtk_widget_show(GTK_WIDGET(form1.window));
	
	return TRUE;
}

static void BStoAD (GtkWidget *window, gpointer data) {
	char *ptr1, *ptr2, *ptr3;
	int mth, i;
	char command[255];
	
	ptr1 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox1));
	ptr2 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox2));
	ptr3 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox3));
	
	for (i = 0; i <= 11; i++) {
		if (!strcmp(ptr2, nepmonth[i])) {
			mth = i+1;
			break;
		}
	}
	
	sprintf(command, "BStoAD %s %d %s\n", ptr3, mth, ptr1);
	//printf("year=%s, month=%d day=%s command=%s\n", ptr3, mth, ptr1, command);
	form2Execute(command);
	//printf("%s\n", line);
	gtk_label_set_text (GTK_LABEL(form3.label1), line);
	
}

static void ADtoBS (GtkWidget *window, gpointer data) {
	char *ptr1, *ptr2, *ptr3;
	int mth, i;
	char command[255];
	
	ptr1 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox4));
	ptr2 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox5));
	ptr3 = (char *) gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(form3.comboBox6));
	
	for (i = 0; i <= 11; i++) {
		if (!strcmp(ptr2, engmonth[i])) {
			mth = i+1;
			break;
		}
	}
	
	sprintf(command, "ADtoBS %s %d %s\n", ptr3, mth, ptr1);
	
	form2Execute(command);
	//printf("%s\n", line);
	gtk_label_set_text (GTK_LABEL(form3.label1), line);
	
}

void form3UiDesign(GtkBuilder *builder) {
	form3.window = GTK_WIDGET (gtk_builder_get_object (builder, "window3"));
	form3.label1 = GTK_WIDGET (gtk_builder_get_object (builder, "label4"));
	form3.comboBox1 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext2"));
	form3.comboBox2 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext3"));
	form3.comboBox3 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext4"));
	form3.comboBox4 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext5"));
	form3.comboBox5 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext6"));
	form3.comboBox6 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext7"));
	form3.button1 = GTK_WIDGET (gtk_builder_get_object (builder, "button22"));
	form3.button2 = GTK_WIDGET (gtk_builder_get_object (builder, "button23"));	
	
	
	int j, i = 1;
	char day[5];
	char nepyear[6];
	char engyear[6]; 	
	
	for (i = 1; i <= 32; i++) {
		sprintf(day, "%d",i);
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox1), day);
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox4), day);
	}
	
	for (i = 0; i <= 11; i++) {
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox2), nepmonth[i]);
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox5), engmonth[i]);
	}
	//gtk_combo_box_text_set_active_text  (GTK_COMBO_BOX_TEXT(form3.comboBox5), 1); 
	for (i = 2070, j = 2013 ; j >= 1919 ; i--, j--) {
		sprintf(nepyear, "%d", i);
		sprintf(engyear, "%d", j);
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox3), nepyear);
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(form3.comboBox6), engyear);
	}
	
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox1), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox2), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox3), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox4), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox5), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX(form3.comboBox6), 0);
	
	
}

void form3SignalsConnector() {
	g_signal_connect (G_OBJECT (form3.window), "delete_event", G_CALLBACK (DeleteEvent2), NULL);
	g_signal_connect (G_OBJECT (form3.button1), "clicked", G_CALLBACK (BStoAD), NULL);
	g_signal_connect (G_OBJECT (form3.button2), "clicked", G_CALLBACK (ADtoBS), NULL);
}


