#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

GtkBuilder *builder;

#include "structure.c"
#include "Form1.c"
#include "Form2.c"
#include "form_3.c"


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "home.ui", NULL);
	
	form1UiDesign(builder);
	form1SignalsConnector();
	
	form2UiDesign(builder);
	form2SignalsConnector();	
	
	form3UiDesign(builder);
	form3SignalsConnector();	
	
	gtk_widget_show (GTK_WIDGET(form1.window));
	
	gtk_main();
	return 0;
}
	
