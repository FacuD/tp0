#include "server.h"

int main(void)
{
    server_logger = NULL;
    server_logger = log_create("./logs/server.log", "Servidor", 1, LOG_LEVEL_DEBUG);

    int server_fd = iniciar_servidor();
    log_info(server_logger, "Servidor listo para recibir al cliente");
    int cliente_fd = esperar_cliente(server_fd);

    t_list *lista;
    while (1)
    {
        int cod_op = recibir_operacion(cliente_fd);
        switch (cod_op)
        {
        case MENSAJE:
            recibir_mensaje(cliente_fd);
            break;
        case PAQUETE:
            lista = recibir_paquete(cliente_fd);
            log_info(server_logger, "Me llegaron los siguientes valores:\n");
            list_iterate(lista, (void *)iterator);
            break;
        case -1:
            log_error(server_logger, "el cliente se desconecto. Terminando servidor");
            return EXIT_FAILURE;
        default:
            log_warning(server_logger, "Operacion desconocida. No quieras meter la pata");
            break;
        }
    }
    return EXIT_SUCCESS;
}

void iterator(char *value)
{
    log_info(server_logger, "%s", value);
}
