# EJERCICIO 1
# Genere una grilla regular entre -50 y +50 de 1000 puntos y grafique 
# sobre una misma salida las siguientes funciones: sin(x), cos(x) y cos (x^2)

x_values <- seq(from = -50, to = 50, length.out = 1000 )

f1 <- sin(x_values)
f2 <- cos(x_values)
f3 <- cos(x_values^2)

plot(x_values, f1, type = "l", col = "blue", ylab = "y", xlab = "x", label = "f_1")
lines(x_values, f2, col="red")
lines(x_values, f3, col="green")
legend("topright", legend = c("sin(x)", "cos(x)", "cos(x^2)"),
       col = c("blue", "red", "green"), lty = 1)

# EJERCICIO 2
# Estime por simulación la probabilidad de que en un curso de 20 personas haya 
# dos que cumplan el mismo día. Suponga que el año tiene 365 días.
# Se trata del problema probabilístico del cumpleaños con N=20.

prod <- 1
for(i in 346:365) prod <- prod*i                  

p_ninguno_coincide = prod/(365^20)				        # P(ninguno)= (365/365)*...*(346/365) = (365*...*346)/365^20
p_al_menos_dos_coinciden = 1-p_ninguno_coincide		# P(al menos dos coinciden) = 1 - P(ninguno)

print(p_al_menos_dos_coinciden)

# EJERCICIO 3
# Ingresar la siguiente matriz A en R
# A = [1, 4, 5; 1, 3, 1; 2, 0, 4] y el siguiente vector b = [1, -1, 3]
# Obtenga el determinante de A y resuelva el sistema Ax = b

A <- matrix( c(1, 4, 5, 1, 3, 1, 2, 0, 4), nrow = 3, ncol = 3, byrow = TRUE)
b <- c(1, -1, 3)

det(A)

x <- solve(A, b)

print(x)

# EJERCICIO 4
# Se busca aproximar √2. Para eso se propone el siguiente esquema iterativo:
# a_o=1 a_{n+1}=a_n/2+1/a_n
# a) Implementar una función aprox1 que dado un n 
# aproxime √2 haciendo n iteraciones. 
# b) Implementar una función aprox2 que dado un ε > 0, aproxime √2 cuando 
# la diferencia entre an y an+1 sea menor (en valor absoluto) que ε.

aprox1 <- function(n)
{
  a <- 1
  for(i in 1:n)
  {
    a <- a/2+1/a
  }
  return(a)
}

aprox2 <- function(epsilon)
{
  a_prev <- 1
  delta <- epsilon + 1
  while(delta>epsilon)
  {
    a <- a_prev/2 + 1/a_prev
    delta <- abs(a-a_prev)
    a_prev <- a
  }
  
  return(a)
}

# Ejemplos de prueba de las funciones

sqrt2_aprox1 = aprox1(500)
sqrt2_aprox2 = aprox2(1e-5)

print(sqrt2_aprox1)
print(sqrt2_aprox2)










