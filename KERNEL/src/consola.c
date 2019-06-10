#include "consola.h"

#define ever ;;
#define OR ||
#define AND &&

void consola() {
    
    for(ever) {
        char* linea = console();

        if(string_equals_ignore_case(linea,"EXIT")) {
                free(linea);
                break;
        }

        procesar_comando(linea);

        free(linea);
    }
    pthread_exit(0);
    //exit(EXIT_SUCCESS);
}

void crear_pcb (char* string_codigo, t_tipo_request tipo) {
    t_PCB* pcb = malloc( sizeof(t_PCB) );
    pcb->request_comando = strdup( string_codigo );
    pcb->pc = 0;
    pcb->tipo_request = tipo;
    pcb->id = id_pcbs;

    list_add( l_pcb_nuevos , pcb );

    log_info(logger, "Se crea el PCB de la request: %s con id: %d ", pcb->request_comando , pcb->id);

    id_pcbs++;
}

unsigned long long obtener_tiempo_actual (void) { //revisar por qué no reconoce el "tv" que en las pruebas del Eclipse sí anda...
    struct timeval tv;
	unsigned long long milisegundos_unix_epoch;
    gettimeofday(&tv, NULL);
    milisegundos_unix_epoch = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
    return milisegundos_unix_epoch;
}


void procesar_comando(char* linea) {
    char** parametros = string_split(linea, " ");
	int cantParametros = split_cant_elem(parametros);

    if (string_equals_ignore_case(parametros[0], "SELECT") || string_equals_ignore_case(parametros[0], "INSERT") ||
    	string_equals_ignore_case(parametros[0], "CREATE") || string_equals_ignore_case(parametros[0], "DROP")	)
    {

    	t_tipo_request tipo = SIMPLE;
    	crear_pcb( linea , tipo );

    	/*TODO: si quieren aca se puede chequear en funciones auxiliares los parametros segun el tipo de comando que ingresa
    	 * es decir if(parametro[0] == select) chequear_select y asi con las demas y listo. pero la idea es que aca se cree el pcb de todos estos comandos)
    	 */

        if (cantParametros == 3) {
            //  Ejemplo: SELECT nombre_de_la_tabla key

            //  nombre_de_la_tabla = parametros[1];
            //  key = paramentros[2];

            /*
            criterio_de_consistencia_asociado = obtener_criterio_consistencia_tabla(nombre_de_la_tabla);

            if (strcmp(criterio_de_consistencia_asociado, "SC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(numero_memoria_con_criterio_SC);
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(numero_memoria_con_criterio_SC);
            }
            else if (strcmp(criterio_de_consistencia_asociado, "SHC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
            }
            else if (strcmp(criterio_de_consistencia_asociado, "EC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
            }

            delegar_select_a_memoria(memoria_ip, memoria_puerto, nombre_de_la_tabla, key);

            loggear();
            recibir_resultados_de_memoria();
            mostrar_resultados();
            */
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "INSERT")) {
        if (cantParametros == 4) {
            //  Ejemplo: INSERT nombre_de_la_tabla key value

            //  nombre_de_la_tabla = parametros[1];
            //  key = parametros[2];
            //  value = parametros[3];

            /*
            criterio_de_consistencia_asociado = obtener_criterio_consistencia_tabla(nombre_de_la_tabla);

            if (strcmp(criterio_de_consistencia_asociado, "SC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(numero_memoria_con_criterio_SC);
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(numero_memoria_con_criterio_SC);
            }
            else if (strcmp(criterio_de_consistencia_asociado, "SHC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
            }
            else if (strcmp(criterio_de_consistencia_asociado, "EC")) {
                memoria_ip = obtener_ip_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
                memoria_puerto = obtener_puerto_memoria_de_lista_pool_memorias(funcion_hash(key, cantidad_memorias_actuales_pool_de_memorias));
            }
            */
            //  delegar_insert_a_memoria(memoria_ip, memoria_puerto, nombre_de_la_tabla, key, value);

            //  loggear();
            //  recibir_resultados_de_memoria();
            //  mostrar_resultados();
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "CREATE")) {
        if (cantParametros == 5) {
            //  Ejemplo: CREATE nombre_de_la_tabla tipo_de_consistencia cantidad_de_particiones tiempo_de_compactacion
            
            //  nombre_de_la_tabla = parametros[1];
            //  tipo_de_consistencia = parametros[2];
            //  cantidad_de_particiones = parametros[3];
            //  tiempo_de_compactacion = parametros[4];

            //  Se delega DIRECTAMENTE a la memoria del archivo de configuración.
            //  delegar_create(memoria_ip, memoria_puerto, nombre_de_la_tabla, tipo_de_consistencia, cantidad_de_particiones, tiempo_de_compactacion);

            //  loggear();
            //  recibir_resultados_de_memoria();
            //  mostrar_resultados();
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "DESCRIBE")) {
        if (cantParametros == 1) {
            //  Ejemplo (único): DESCRIBE
            
            //  Se delega DIRECTAMENTE a la memoria del archivo de configuración.
            //  delegar_describe_global(memoria_ip, memoria_puerto);    

            //  loggear();
            //  recibir_resultados_de_memoria();
            //  mostrar_resultados();       
        }
        else
        if (cantParametros == 2) {
            //  Ejemplo: DESCRIBE nombre_de_la_tabla

            //  nombre_de_la_tabla = parametros[1];

            //  Se delega DIRECTAMENTE a la memoria del archivo de configuración.
            //  delegar_describe_1_tabla(memoria_ip, memoria_puerto, nombre_de_la_tabla); 

            //  loggear();
            //  recibir_resultados_de_memoria();
            //  mostrar_resultados();
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "DROP")) {
        if (cantParametros == 2) {
            //  Ejemplo: DROP nombre_de_la_tabla

            //  nombre_de_la_tabla = parametros[1];
            int* nombre_de_la_tabla = parametros[1];
            printf("Se DROPea la tabla %s.\n", nombre_de_la_tabla);
            
            //  Se delega DIRECTAMENTE a la memoria del archivo de configuración.
            //  delegar_drop(memoria_ip, memoria_puerto, nombre_de_la_tabla); 

            //  loggear();
            //  recibir_resultados_de_memoria();
            //  mostrar_resultados();
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }    
    else

    //  Los siguientes 4 casos son tareas que realiza el Kernel en particular...

    if (string_equals_ignore_case(parametros[0], "JOURNAL")) {
        if (cantParametros == 1) {
            //  Ejemplo: JOURNAL
            //  No tiene otros parámetros

            //  ...laburar acá...
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "ADD") AND string_equals_ignore_case(parametros[1], "MEMORY") AND string_equals_ignore_case(parametros[3], "TO")) {
        if (cantParametros == 5) {
            //  Ejemplo: ADD MEMORY numero_de_memoria TO tipo_de_consistencia
            int numero_de_memoria = atoi(parametros[2]);
            char* tipo_de_consistencia = parametros[4];

            //  PRUEBA_DEL_BARRA_N clean_new_line_ch
            limpiar_caracter_final_de_nueva_linea(tipo_de_consistencia);
            //  FIN PRUEBA

            //TODO refactor de esto, SC tambien sera una lista no se va a guardar en un int
            if (string_equals_ignore_case(tipo_de_consistencia, "SC")) {
                //numero_memoria_con_criterio_SC = numero_de_memoria;
                printf("Se agrega la memoria %d al criterio SC.\n", numero_de_memoria);

                //  ...se labura acá...
                //numero_memoria_con_criterio_SC = numero_de_memoria;

                //printf("Número de memoria con criterio SC: %d\n", numero_memoria_con_criterio_SC);

            }
            else 
                if (string_equals_ignore_case(tipo_de_consistencia, "SHC")) {
                    printf("Se agrega la memoria %d al criterio SHC.\n", numero_de_memoria);

                    //  ...se labura acá...

                }
                else {
                    if (string_equals_ignore_case(tipo_de_consistencia, "EC")) {
                    printf("Se agrega la memoria %d al criterio EC.\n", numero_de_memoria);
                    
                    //  ...se labura acá...

                    }
                    else {
                        notificar_error_tipo_consistencia();
                    }
                }
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "RUN")) {
        if (cantParametros == 2) {
            //  Ejemplo: RUN ruta_del_archivo_LQL
            
            char* ruta_del_archivo_LQL = parametros[1];
            FILE *archivo = NULL;
            archivo = fopen(ruta_del_archivo_LQL, "r");

            if (archivo == NULL) {
                puts("Archivo no encontrado.");
            }
            

            //TODO aca se tiene que ejecutar crear_pcb y listo con el tipo_request en 1 (compuesta)


            size_t buffer_size = 100;
            char *lineaLeida = malloc(buffer_size * sizeof(char));

            int numero_de_linea = 0;
            while (getline(&lineaLeida, &buffer_size, archivo) != -1) {
                if (strcmp(lineaLeida, "\n")) printf("%s", lineaLeida);
                
                procesar_comando(lineaLeida);

            }
            fflush(stdout);
            fclose(archivo);
            free(lineaLeida);          
            
            /*   
            else {
                while (!feof(archivo))
                {
                    fgets(lineaLeida, 100, archivo);
                    if (strcmp(lineaLeida, "\n") != 0) { //el archivo no debe terminar con un "\n". Si no, falla (duplica la última línea leída).
                        printf("%s", lineaLeida);

                        procesar_comando(lineaLeida);
                        //  y todo lo demás...

                        /* Al ingresar por consola RUN 2.LQL, se muestra lo siguiente
                                    ADD MEMORY 1 TO SC
                        NO -------> Error: criterio de consistencia incorrecto.
                                    ADD MEMORY 2 TO SHC
                        NO -------> Error: criterio de consistencia incorrecto.
                                    ADD MEMORY 3 TO EC
                        NO -------> Error: criterio de consistencia incorrecto.
                                    ADD MEMORY 4 TO SC
                        NO -------> Error: criterio de consistencia incorrecto.
                        CASI -----> ADD MEMORY 5 TO SHCSe agrega la memoria 5 al criterio SHC
                        ? --------> .

                        En los primeros 4 casos:
                        Me parece que el último parámetro guarda el "\n" (¿será culpa de fgets? eso)... por eso falla al compararlo con "SC", o con "SHC" o con "EC".
                        En el último caso, cuando no hay "\n", anda bien digamos...


                        Por otro lado: si se pone un archivo que no existe, el programa muestra "Ruta del archivo incorrecta" y termina.
                        Hay que corregirlo...
                        
                    }
                }
                printf("\n");
            }
            
            fclose(archivo);
            */
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else
    if (string_equals_ignore_case(parametros[0], "METRICS")) {
        if (cantParametros == 1) {
            //  Ejemplo: METRICS 
            //  No tiene otros parámetros

            //  ...laburar acá...
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    else

    //  Comando "clear" para limpiar la pantalla de la consola
    if (string_equals_ignore_case(parametros[0], "CLEAR")) {
        if (cantParametros == 1) {
            system("clear");
        }
        else {
            notificar_error_sintactico_en_parametros();
        }
    }
    
    //  Si no se ingresa ningún comando...
    else {
        notificar_error_sintactico_en_comando();
    }

	split_liberar(parametros);
}

void notificar_error_sintactico_en_comando(void) {
    puts("Error sintáctico: comando incorrecto.");
}

void notificar_error_sintactico_en_parametros(void) {
    puts("Error sintácico: cantidad de parámetros incorrecta.");
}

void notificar_error_tipo_consistencia(void) {
    puts("Error: criterio de consistencia incorrecto.");
}

//  PRUEBA_DEL_BARRA_N clean_new_line_ch
/*void limpiar_caracter_final_de_nueva_linea(char *linea) {
    int posicion_nueva_linea = strlen(linea) - 1;
    if (linea[posicion_nueva_linea] == '\n') linea[posicion_nueva_linea] = '\0';
}*/
//  FIN PRUEBA