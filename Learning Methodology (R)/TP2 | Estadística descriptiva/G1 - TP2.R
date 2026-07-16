library(e1071)

#EJERCICIO 1

graduados <- scan("graduados.txt")

# a)

media <- mean(graduados)
mediana <- median(graduados)
# La consigna no especifica si se Se poda un 10% en total o de cada lado
# Se opta por la segunda opción
media_po <- mean(graduados, trim = 0.10)

cat("Media: ", media, "\n")
cat("Mediana: ", mediana, "\n")
cat("Media podada 10%: ", media_po, "\n")

#b)

desvio <- sd(graduados)
rango_intercuartil <- IQR(graduados)
mad <- mad(graduados)

cat("Desvío estándar: ", desvio, "\n")
cat("Rango intercuartil: ", rango_intercuartil, "\n")
cat("MAD: ", mad, "\n")

#c)

boxplot(graduados, main = "Diagrama de caja de promedios de graduados", 
        ylab= "Promedios")

writeLines("OBSERVACIONES\n 
            El 50% de los datos se encuentra aproximadamente entre 3.6 y 3.8. 
            Tiene una distribucion simetrica. No hay valores atipicos en el 
            conjunto de datos.")

#d)

# Se puede verificar normalidad visualmente mediante un histograma. Si el 
# histograma tiene forma de campana de Gauss, es posible asumir que los datos
# están normalmente distribuidos.

hist(graduados, col = "lightblue", 
     main = "Histograma de promedios de graduados", xlab = "promedios",
     border = "black")

# Se determina que la forma del histograma no es lo suficientemente concluyente
# como para suponer normalidad.
# Como segunda prueba visual, se realiza un gráfico Q-Q y se verifica que los
# datos se ajusten a la recta que denota normalidad.

qqnorm(graduados, main = "Q-Q Plot")
qqline(graduados, col = "red")

# Se observa que los datos se ajustan bien a la línea,  por lo que puede 
# suponerse normalidad. 
# Para obtener una prueba más concluyente, se lleva a cabo un método analítico.
# Se realiza una prueba de Shapiro-Wilk con un nivel de significancia del 5%. 
# Si el p-valor es mayor a 0.05, se puede suponer normalidad.

graduados.test <- shapiro.test(graduados)
print(graduados.test)
 
print("Es razonable suponer que los datos están normalmente distribuidos.")


#EJERCICIO 2

#a)

datos <- read.table("ciudades.txt", header = TRUE)
head(datos)
boxplot(datos, main = "Boxplot de las 10 ciudades más pobladas (1967)", 
        xlab = "Países", ylab = "Población (cientos de miles)", 
        col = c("yellow", "green", "red", "pink"))

#b)

# Centros: medias
medias <- apply(datos, 2, mean)

# Disperiones: desvíos estándar 
desv_estandar <- apply(datos, 2, sd)

# Simetrías: coeficiente de simetría y curtosis
simetrias <- apply(datos, 2, skewness)
curtosis <- apply(datos, 2, kurtosis)

resumen_paises <- data.frame(
  Pais = colnames(datos),
  Media = medias,
  DesviacionEstandar = desv_estandar,
  Simetria = simetrias,
  Curtosis = curtosis
)

print(resumen_paises)

writeLines("OBSERVACIONES:\n
      1. EEUU y Japón tienen medias más altas que Argentina y Holanda, lo cual
      es un indicio de que contienen una mayor cantidad de personas.\n
      2. La mayor desviación estándar la tiene Japón, lo que indica que es el
      país más homogéneamente poblado, ya que su distribución de población
      presenta mayor dispersión. Le sigue EEUU, luego Argentina y por último 
      Holanda.\n
      3. Los cuatro países presentan un coeficiente de simetría positivo, lo que
      indica un sesgo positivo de los datos de la población. El menor sesgo lo
      tiene Holanda, cuyo coeficiente de simetría es cercano a 0 (lo que 
      indicaría que los datos son simétricos). Por lo tanto, Holanda presenta 
      la mayor simetría y le sigue EEUU. Argentina y Japón presentan mayor
      asimetría, siendo el primero el más asimétrico de los cuatro.\n
      4. Holanda presenta un coeficiente de curtosis negativo, lo que indica una
      baja concentración de los datos en torno a la media. El resto de los 
      países poseen curtosis positivas, por lo que sus datos se concentran en 
      torno a sus respectivas medias estadísticas, siendo Argentina el país de
      mayor curtosis, seguido por Japón y luego EEUU. Es fácil ver que, al igual
      que el desvío estándar, el coeficiente de curtosis también es una medida 
      de la dispersión de los datos. \n")
      
#EJERCICIO 3

datos <- read.table("hierro.txt", header = TRUE)

# Boxplots
par(mfrow = c(1, 2))
boxplot(datos$Fe3, main = "Boxplot de Fe3+", ylab = "Porcentaje retenido")
boxplot(datos$Fe2, main = "Boxplot de Fe2+", ylab = "Porcentaje retenido")
par(mfrow = c(1, 1))

# Histogramas
par(mfrow = c(1, 2)) # Mostrar dos graficos al mismo tiempo
hist(datos$Fe3, main = "Histograma de Fe3+", xlab = "Porcentaje retenido", 
     col = "yellow", border = "black", breaks = 10)
hist(datos$Fe2, main = "Histograma de Fe2+", xlab = "Porcentaje retenido", 
     col = "red", border = "black", breaks = 10)
par(mfrow = c(1, 1)) # Configuracion normal

# Q-Q plots
par(mfrow = c(1, 2))
qqnorm(datos$Fe3, main = "QQ-plot de Fe3+")
qqline(datos$Fe3, col = "red", lwd = 2)

qqnorm(datos$Fe2, main = "QQ-plot de Fe2+")
qqline(datos$Fe2, col = "violet", lwd = 2)
par(mfrow = c(1, 1))

writeLines("OBSERVACIONES\n
           Una distribución normal reflejaría una forma de campana en cada 
           histograma. En este caso ambos histogramas presentan un sesgo hacia 
           la izquierda.\n
           En los gráficos Q-Q los datos se desvían considerablemente de la 
           linea de referencia, por lo que se concluye que no es normal.")

# Verifico analíticamente con una prueba de Shapiro-Wilk
print(shapiro.test(datos$Fe3))
print(shapiro.test(datos$Fe2))

# Los p-valores en ambos casos son menores a 0.05, por lo que los datos no 
# están normalmente distribuidos.


#b)

# Transformación logarítmica
log_Fe3 <- log(datos$Fe3)
log_Fe2 <- log(datos$Fe2)

# Boxplots
par(mfrow = c(1, 2))
boxplot(log_Fe3, main = "Boxplot de log(Fe3+)", 
        ylab = "Logaritmo del porcentaje retenido")
boxplot(log_Fe2, main = "Boxplot de log(Fe2+)", 
        ylab = "Logaritmo del porcentaje retenido")
par(mfrow = c(1, 1))

# Histogramas
par(mfrow = c(1, 2))
hist(log_Fe3, main = "Histograma de log(Fe3+)",
     xlab = "Logaritmo del porcentaje retenido", col = "yellow", 
     border = "black", breaks = 10)
hist(log_Fe2, main = "Histograma de log(Fe2+)", 
     xlab = "Logaritmo del porcentaje retenido", col = "red", 
     border = "black", breaks = 10)
par(mfrow = c(1, 1))

# Q-Q plots
par(mfrow = c(1, 2))
qqnorm(log_Fe3, main = "QQ-plot de log(Fe3+)")
qqline(log_Fe3, col = "red", lwd = 2)

qqnorm(log_Fe2, main = "QQ-plot de log(Fe2+)")
qqline(log_Fe2, col = "violet", lwd = 2)
par(mfrow = c(1, 1))

writeLines("OBSERVACIONES\n
           Contrastando con el caso anterior, la aplicación del logaritmo ha 
           normalizado las curvas, haciendo que se vea en el histograma la 
           forma característica de campana. En los gráficos Q-Q, los puntos no 
           se alejan significativamente de la curva. Por lo tanto, es posible 
           afirmar que las distribuciones se pueden modelar con una normal.")

# Verifico analíticamente con una prueba de Shapiro-Wilk
print(shapiro.test(log_Fe3))
print(shapiro.test(log_Fe2))

# Los p-valores en ambos casos son mayores a 0.05, por lo que se acepta que
# ambas disrtibuciones se pueden modelar con una normal.


# EJERCICIO 4

datos_cpu <- scan("cpu.txt")

#a)

media <- mean(datos_cpu)
mediana <- median(datos_cpu)
media_podada <- mean(datos_cpu, trim = 0.1)

cat("Media muestral: ", media, "\n")
cat("Mediana muestral: ", mediana, "\n")
cat("Media α-podada ", media_podada, "\n")

#b)

desvio_estandar <- sd(datos_cpu)
rango_intercuartil <- IQR(datos_cpu)
cat("Desvío estándar: ", desvio_estandar, "\n")
cat("Rango intercuartil:", rango_intercuartil, "\n")

#c)

par(mfrow = c(1, 2))
hist(datos_cpu, main = "Hist. de tiempos de CPU", 
     xlab = "Tiempo de CPU (segundos)", ylab = "Frecuencia", col = "red", 
     border = "black", breaks = 5)
boxplot(datos_cpu, main = "Boxplot de tiempos de CPU", 
        ylab = "Tiempo de CPU (segundos)", col = "green")
par(mfrow = c(1, 1)) 

writeLines("OBSERVACIONES:\n
           El histograma esta sesgado hacia la derecha.\n
           El boxplot presenta muchos outliers.")

#d)

writeLines("Para analizar si los datos son normales analizamos el histograma y 
      además realizamos un Q-Q plot.")
qqnorm(datos_cpu, main = "Q-Q plot de tiempos de CPU")
qqline(datos_cpu, col = "violet", lwd = 2)
writeLines("Los datos no presentan una distribución normal por varias razones: 
      el histograma ya mencionado presenta un sesgo a derecha y no una
      distribución de forma de campana; también, los puntos del QQPlot se alejan 
      mucho a la recta trazada.")

# Verifico analíticamente con una prueba de Shapiro-Wilk:
print(shapiro.test(datos_cpu))
# p-valor < 0.05, por lo que los datos no están normalmente distribuidos.

#e)

writeLines("Considerando que el boxplot presenta muchos outliers, la mediana es 
           la mejor medida de posición para describir el centro de datos, ya que
           al tener demasiados valores atípicos obtenemos un desplazamiento de 
           la media que no refleja los datos.")

