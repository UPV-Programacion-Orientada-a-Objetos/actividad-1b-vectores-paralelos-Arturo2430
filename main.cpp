#include <iostream>
#include <limits>

// Prototipos de funcion
void menu();
void consultar_producto();
void encontrar_producto_mas_caro();
void reporte_inventario();
void actualizar_stock();
int verificar_numero_entero(std::istream&);

// Variables globales
int prod_codigos[100] = {101, 102, 103, 104, 105};
std::string prod_nombres[100] = {"Martillo de bola", "Destornillador", "Cinta métrica", "Llave inglesa", "Taladro inalámbrico"};
int stocks[100] = {50, 120, 75, 45, 10};
float precios_unitarios[100] = {15.50, 8.75, 20.00, 25.99, 120.00};
int productos_existentes = 5;

int main() {
    int caso;
    bool loop = true;
    std::cout << "--- Bienvenido al Sistema de Inventario de El Martillo ---" << std::endl;
    do {
        menu();
        caso = verificar_numero_entero(std::cin);
        switch (caso) {
            case 1:
                consultar_producto();
                break;
            case 2:
                actualizar_stock();
                break;
            case 3:
                reporte_inventario();
                break;
            case 4:
                encontrar_producto_mas_caro();
                break;
            case 5:
                std::cout << "\nSaliendo del programa. Nos vemos :D" << std::endl;
                loop = false;
                break;
            default:
                std::cout << "ERROR: La Opcion " << caso << " no esta dentro del menu." << std::endl;
                break;
        }
    } while (loop);


    return 0;
}

// Funciones Reutilizables

void menu() {
    std::cout << "\n================ Menú principal ===================" << std::endl;
    std::cout << "[1] Consultar un producto" << std::endl;
    std::cout << "[2] Actualizar inventario" << std::endl;
    std::cout << "[3] Generar reporte completo" << std::endl;
    std::cout << "[4] Encontrar el producto más caro" << std::endl;
    std::cout << "[5] Salir" << std::endl;
    std::cout << "===================================================" << std::endl;
    std::cout << "\nOpcion Seleccionada: ";
}

/**
 * Funcion para encontrar un indice de un array mediante la comparacion de codigos
 * @param cod Codigo del producto a buscar
 * @return Indice del producto encontrado o -1 si el codigo no existe
 */
int encontrar_indice_por_codigo(int cod) {
    for (int i=0; i < productos_existentes; i++) {
        if (prod_codigos[i] == cod) return i;
    }
    return -1;
}

/**
 * Funcion para actualizar el stock de un producto validando que no quede en negativo
 * @param index Indice del producto en los vectores paralelos
 * @param num Cantidad a agregar (Puede ser negativa para reducir el stock)
 */
void actualizador_stock(int index, int num) {
    int aux;
    do {
        aux = stocks[index];
        aux += num;
        if (aux < 0) {
            std::cout << "El stock restante no puede ser negativo. Ingrese otro numero: ";
            num = verificar_numero_entero(std::cin);
        }
    } while (aux < 0);
    stocks[index] += num;
    std::cout << "Nuevo stock: " << stocks[index] << std::endl;
}

/**
 * Funcion para validar la entrada del usuario garantizando un numero entero valido.
 * @param cin Flujo de entrada para leer datos
 * @return Numero entero valido
 */
int verificar_numero_entero(std::istream& cin){
    int aux = 0;
    while(true) {
        cin >> aux;
        if(cin.fail()){
            cin.clear();
            // Descarta la linea incorrecta del buffer de la entrada
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Entrada invalida. Necesita ingresar un numero entero valido: ";
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return aux;
        }
    }
}

void informacion_producto(int indice) {
    std::cout << "\n--- Informacion del Producto ---" << std::endl;
    std::cout << "Codigo del producto: " << prod_codigos[indice] << std::endl;
    std::cout << "Nombre del producto: " << prod_nombres[indice] << std::endl;
    std::cout << "Cantidad en stock: " << stocks[indice] << std::endl;
    std::cout << "Precio Unitario: " << precios_unitarios[indice] << std::endl;
}

void consultar_producto() {
    int cod, indice;
    std::cout << "\nIngrese el codigo del producto que desea consultar: ";
    cod = verificar_numero_entero(std::cin);
    indice = encontrar_indice_por_codigo(cod);
    if (indice == -1) {
        std::cout << "\nNo existe un producto con ese codigo." << std::endl;
    } else {
        informacion_producto(indice);
    }
}

void encontrar_producto_mas_caro() {
    int indice = 0;
    for (int i=0; i < productos_existentes; i++) {
        if (precios_unitarios[i] >= precios_unitarios[indice]) indice = i;
    }

    std::cout << "\nEl producto mas caro es " + prod_nombres[indice] + " con un precio de $" << precios_unitarios[indice] << std::endl;
}

void reporte_inventario() {
    std::cout << "\n--- Reporte de Inventario ---" << std::endl;
    std::cout << "Codigo\t | Nombre\t\t\t | Stock | Precio" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    for (int i = 0 ; i < productos_existentes; i++) {
        std::cout << prod_codigos[i] << "\t| " + prod_nombres[i] + "\t\t\t | " << stocks[i] << " | $" << precios_unitarios[i] << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "\n--- Fin del Reporte ---" << std::endl;
}

void actualizar_stock() {
    int cod, indice, num;
    std::cout << "Ingrese el codigo del producto que desea actualizar: ";
    cod = verificar_numero_entero(std::cin);
    indice = encontrar_indice_por_codigo(cod);
    if (indice == -1) {
        std::cout << "ERROR: No existe un producto con ese codigo." << std::endl;
        return;
    }

    std::cout << "Ingrese un numero para actualizar el stock: ";
    num = verificar_numero_entero(std::cin);
    actualizador_stock(indice, num);
}