import matplotlib.pyplot as plt
from scipy.stats import linregress
import numpy as np

# ------ Datos Dijkstra - Tomás ------
# Resultados ejecución v = 2^10
# v_10 = 1024
# e_values_v10 = [2**16, 2**17, 2**18]
# tiempos_heap_v10 = [0.0293355, 0.0410768, 0.0632075]
# tiempos_fib_v10 = [0.0292195, 0.0418358, 0.0634673]

# # Resultados de la ejecución v = 2^12
# v_12 = 4096
# e_values_v12 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v12 = [0.0682943, 0.0855679, 0.108612, 0.154018, 0.23431, 0.386005, 0.724239]
# tiempos_fib_v12 = [0.0703663, 0.0873595, 0.109283, 0.151956, 0.234921, 0.380209, 0.710147]

# # Resultados de la ejecución v = 2^14
# v_14 = 16384
# e_values_v14 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v14 = [0.197024, 0.218724, 0.250768, 0.302932, 0.394438, 0.577309, 0.934493]
# tiempos_fib_v14 = [0.202212, 0.223761, 0.247099, 0.310485, 0.404734, 0.582707, 0.917147]

# ------ Datos Dijkstra - Felipe ------

# Resultados ejecución v = 2^10
# v_10 = 1024
# e_values_v10 = [2**16, 2**17, 2**18]
# tiempos_heap_v10 = [0.0082358, 0.0110751, 0.0181433]
# tiempos_fib_v10 = [0.00988578, 0.0126283, 0.0216387]

# # Resultados de la ejecución v = 2^12
# v_12 = 4096
# e_values_v12 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v12 = [0.020703, 0.0257532, 0.0322007, 0.0482332, 0.0767112, 0.116196, 0.26939]
# tiempos_fib_v12 = [0.0274966, 0.0321052, 0.0392745, 0.0550829, 0.0842927, 0.127408, 0.291776]

# # Resultados de la ejecución v = 2^14
# v_14 = 16384
# e_values_v14 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v14 = [0.0713887, 0.0786391, 0.0900607, 0.106309, 0.1354, 0.184299, 0.289496]
# tiempos_fib_v14 = [0.0910601, 0.0992355, 0.110827, 0.129052, 0.157266, 0.212939, 0.319063]

# ------ Datos Dijkstra - Pepe ------

# Resultados ejecución v = 2^10

# v_10 = 1024
# e_values_v10 = [2**16, 2**17, 2**18]
# tiempos_heap_v10 = [0.00806666, 0.011579, 0.0184721]
# tiempos_fib_v10 = [0.00912556, 0.0128118, 0.0194764]

# # Resultados de la ejecución v = 2^12

# v_12 = 4096
# e_values_v12 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v12 = [0.0214876, 0.0257103, 0.0362634, 0.0532524, 0.0733603, 0.125729, 0.269347]
# tiempos_fib_v12 = [0.0276048, 0.0307123, 0.0418137, 0.0607421, 0.0789091, 0.132089, 0.278988]

# # Resultados de la ejecución v = 2^14

# v_14 = 16384
# e_values_v14 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
# tiempos_heap_v14 = [0.0760887, 0.0836692, 0.0955148, 0.111862, 0.141777, 0.195753, 0.300303]
# tiempos_fib_v14 = [0.0968109, 0.103611, 0.115917, 0.131996, 0.16213, 0.215901, 0.31831]

# ------ Datos Dijkstra - Pepe2 ------
# Resultados ejecución v = 2^10
v_10 = 1024
e_values_v10 = [2**16, 2**17, 2**18]
tiempos_heap_v10 = [0.00904512, 0.0134688, 0.0202654]
tiempos_fib_v10 = [0.00973792, 0.0139449, 0.020393]
# Resultados de la ejecución v = 2^12
v_12 = 4096
e_values_v12 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
tiempos_heap_v12 = [0.0223414, 0.0263381, 0.0344808, 0.0487404, 0.0771131, 0.132658, 0.27437]
tiempos_fib_v12 = [0.02548, 0.0298073, 0.0372298, 0.0516085, 0.0803004, 0.133856, 0.277593]
# Resultados de la ejecución v = 2^14
v_14 = 16384
e_values_v14 = [2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22]
tiempos_heap_v14 = [0.0762965, 0.0846852, 0.0965036, 0.114566, 0.142247, 0.198679, 0.305145]
tiempos_fib_v14 = [0.0915367, 0.0990809, 0.11102, 0.128565, 0.154046, 0.209235, 0.313844]

# Función para realizar la regresión lineal y obtener la pendiente
def fitting(e_values, tiempos):
    # Convertir a numpy arrays
    e_values = np.array(e_values)
    tiempos = np.array(tiempos)
    
    # Realizar la regresión lineal
    slope, intercept, r_value, p_value, std_err = linregress(e_values, tiempos)

    # Calcular la recta de ajuste
    ajuste = slope * e_values + intercept
    
    return slope, ajuste, r_value

def graficar_resultados(e_values, tiempos_heap, tiempos_fib, v, subplot_position):
    pendiente_heap, ajuste_heap, r_value_heap = fitting(e_values, tiempos_heap)
    pendiente_fib, ajuste_fib, r_value_fib = fitting(e_values, tiempos_fib)
    
    plt.subplot(3, 1, subplot_position)
    # Muestro el valor del coeficiente de determinación en la leyenda
    plt.plot(e_values, tiempos_heap, 'o', label=f'Heap - R² = {r_value_heap:.4f}', color='blue')
    #plt.plot(e_values, tiempos_heap, 'o', label=f'Heap', color='blue')
    plt.plot(e_values, ajuste_heap, '-', color='blue')
    plt.plot(e_values, tiempos_fib, 'o', label=f'Fibonacci R² = {r_value_fib:.4f}', color='red')
    plt.plot(e_values, ajuste_fib, '-', color='red')
    plt.xlabel('Cantidad de aristas (e)')
    plt.xticks(e_values, [f'2^{e_val.bit_length()-1}' for e_val in e_values], rotation=45, fontsize=7)
    plt.ylabel('Tiempo (s)')
    plt.legend()
    plt.grid()
    plt.title(f'Regresión Lineal para v = 2^{v}')


# Función principal
def main():
    # Crear la figura
    plt.figure(figsize=(8, 8))

    # Graficar para cada valor de v
    graficar_resultados(e_values_v10, tiempos_heap_v10, tiempos_fib_v10, 10, 1)
    graficar_resultados(e_values_v12, tiempos_heap_v12, tiempos_fib_v12, 12, 2)
    graficar_resultados(e_values_v14, tiempos_heap_v14, tiempos_fib_v14, 14, 3)

    # Ajustar el diseño y mostrar la gráfica
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
