# Ler o CSV gerado
compare <- read.csv("plot_pior_caso.csv", header=TRUE, sep=",", as.is=TRUE)

# Criar um gráfico para a Fila de Prioridade
plot(compare$PRIORIDADE, compare$FILA, type="b", col="red", 
     xlab="Prioridade", ylab="Comparações", 
     main="Fila de Prioridade - Enqueue", pch=19)

# Adicionar grade
grid()

# Criar um novo gráfico para a Heap
plot(compare$PRIORIDADE, compare$HEAP, type="b", col="blue", 
     xlab="Prioridade", ylab="Comparações", 
     main="Max-Heap - Enqueue", pch=19)

# Adicionar grade
grid()

# Plotar os dados em um único gráfico
plot(compare$PRIORIDADE, compare$FILA, type="b", col="red", 
     xlab="Prioridade", ylab="Comparações", 
     main="Fila de Prioridade X Heap - Enqueue", pch=19, 
     ylim=range(c(compare$FILA, compare$HEAP)))

# Adicionar a linha para a heap
lines(compare$PRIORIDADE, compare$HEAP, type="b", col="blue")

# Adicionar legenda
legend("topright", legend=c("Fila de Prioridade", "Heap"), 
       col=c("red", "blue"), pch=c(19, 19), lty=1)

# Adicionar grade
grid()
