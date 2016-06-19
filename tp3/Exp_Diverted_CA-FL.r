load_library <- function(){
  library(DBI)
  library(ggplot2)
}
load_library()
from_db <- function(sql) {
  dbGetQuery(ontime, sql)
}
ontime <- dbConnect(RSQLite::SQLite(), dbname = "ontime.sqlite3")

# Levantar el input de los archivos
avg_CA_2000 <- read.csv("outputR/avg_CA_2000.in", header = FALSE)$V1
avg_FL_2000 <- read.csv("outputR/avg_FL_2000.in", header = FALSE)$V1
# avg_NY_2000 <- read.csv("outputR/avg_NY_2000.in", header = FALSE)$V1
avg_CA_2001 <- read.csv("outputR/avg_CA_2001.in", header = FALSE)$V1
avg_FL_2001 <- read.csv("outputR/avg_FL_2001.in", header = FALSE)$V1
# avg_NY_2001 <- read.csv("outputR/avg_NY_2001.in", header = FALSE)$V1
avg_CA_2002 <- read.csv("outputR/avg_CA_2002.in", header = FALSE)$V1
avg_FL_2002 <- read.csv("outputR/avg_FL_2002.in", header = FALSE)$V1
# avg_NY_2002 <- read.csv("outputR/avg_NY_2002.in", header = FALSE)$V1
avg_CA_2003 <- read.csv("outputR/avg_CA_2003.in", header = FALSE)$V1
avg_FL_2003 <- read.csv("outputR/avg_FL_2003.in", header = FALSE)$V1
# avg_NY_2003 <- read.csv("outputR/avg_NY_2003.in", header = FALSE)$V1
avg_CA_2004 <- read.csv("outputR/avg_CA_2004.in", header = FALSE)$V1
avg_FL_2004 <- read.csv("outputR/avg_FL_2004.in", header = FALSE)$V1
# avg_NY_2004 <- read.csv("outputR/avg_NY_2004.in", header = FALSE)$V1
avg_CA_2005 <- read.csv("outputR/avg_CA_2005.in", header = FALSE)$V1
avg_FL_2005 <- read.csv("outputR/avg_FL_2005.in", header = FALSE)$V1
# avg_NY_2005 <- read.csv("outputR/avg_NY_2005.in", header = FALSE)$V1
avg_CA_2006 <- read.csv("outputR/avg_CA_2006.in", header = FALSE)$V1
avg_FL_2006 <- read.csv("outputR/avg_FL_2006.in", header = FALSE)$V1
# avg_NY_2006 <- read.csv("outputR/avg_NY_2006.in", header = FALSE)$V1
avg_CA_2007 <- read.csv("outputR/avg_CA_2007.in", header = FALSE)$V1
avg_FL_2007 <- read.csv("outputR/avg_FL_2007.in", header = FALSE)$V1
# avg_NY_2007 <- read.csv("outputR/avg_NY_2007.in", header = FALSE)$V1
avg_CA_2008 <- read.csv("outputR/avg_CA_2008.in", header = FALSE)$V1
avg_FL_2008 <- read.csv("outputR/avg_FL_2008.in", header = FALSE)$V1
# avg_NY_2008 <- read.csv("outputR/avg_NY_2008.in", header = FALSE)$V1

# Meses para labels
meses <- c('E', 'F', 'M', 'A', 'M', 'J', 'J', 'A', 'S', 'O', 'N', 'D')

# 10 graficos en uno, el primero blanco
layout(matrix(0:9,1,10), widths = c(1,rep(4, 9)))
# Margen inferior para labels
par(mar = c(4,0,0,0), col = "black")

# Experimento California
A <- matrix(nrow = 24, ncol = 2)
for (i in (1:dim(A)[1])) {
  A[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
  A[i,2] <- 1
}
res <- (solve(t(A)%*%A))%*%t(A)%*%c(avg_CA_2003, avg_CA_2004)
new_res <- rep(0,12)
for (i in (1:length(new_res))) {
  new_res[i] <- res[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2) + res[2]
}
mean_squared_error <- norm(A %*% res - avg_CA_2005, "2")

B <- matrix(nrow = 24, ncol = 3)
for (i in (1:dim(B)[1])) {
  B[i,1] <- sin(i*pi*2/12)
  B[i,2] <- cos(i*pi*2/12)
  B[i,3] <- 1
}
Bres <- (solve(t(B)%*%B))%*%t(B)%*%c(avg_CA_2003, avg_CA_2004)
Bnew_res <- rep(0,12)
for (i in (1:length(Bnew_res))) {
  Bnew_res[i] <- Bres[1]*sin(i*pi*2/12) + Bres[2]*cos(i*pi*2/12) + Bres[3]
}
Bmean_squared_error <- norm(B %*% Bres - avg_CA_2005, "2")

C <- matrix(nrow = 24, ncol = 3)
for (i in (1:dim(C)[1])) {
  C[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
  C[i,2] <- cos(i*pi/12 - pi/2)^500
  C[i,3] <- 1
}
Cres <- (solve(t(C)%*%C))%*%t(C)%*%c(avg_CA_2003, avg_CA_2004)
Cnew_res <- rep(0,12)
for (i in (1:length(Cnew_res))) {
  Cnew_res[i] <- Cres[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)) + Cres[2]*cos(i*pi/12 - pi/2)^500 + Cres[3]
}
Cmean_squared_error <- norm(C %*% Cres - avg_CA_2005, "2")

# Plot California
plot((1:12), avg_CA_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_CA_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.005), type = 'l')
plot((1:12), avg_CA_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
lines((1:12), Bnew_res, ylim = c(0,0.005))
par(col = "black")
plot((1:12), avg_CA_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
lines((1:12), Bnew_res, ylim = c(0,0.005))
par(col = "black")
plot((1:12), avg_CA_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
text((1:12), Bnew_res, ylim = c(0,0.005), labels = meses)
par(col = "black")
plot((1:12), avg_CA_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)

# Experimento Florida
A <- matrix(nrow = 24, ncol = 2)
for (i in (1:dim(A)[1])) {
  A[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
  A[i,2] <- 1
}
res <- (solve(t(A)%*%A))%*%t(A)%*%c(avg_FL_2003, avg_FL_2004)
new_res <- rep(0,12)
for (i in (1:length(new_res))) {
  new_res[i] <- res[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2) + res[2]
}
mean_squared_error <- norm(A %*% res - avg_FL_2005, "2")

B <- matrix(nrow = 24, ncol = 3)
for (i in (1:dim(B)[1])) {
  B[i,1] <- sin(i*pi*2/12)
  B[i,2] <- cos(i*pi*2/12)
  B[i,3] <- 1
}
Bres <- (solve(t(B)%*%B))%*%t(B)%*%c(avg_FL_2003, avg_FL_2004)
Bnew_res <- rep(0,12)
for (i in (1:length(Bnew_res))) {
  Bnew_res[i] <- Bres[1]*sin(i*pi*2/12) + Bres[2]*cos(i*pi*2/12) + Bres[3]
}
Bmean_squared_error <- norm(B %*% Bres - avg_FL_2005, "2")

C <- matrix(nrow = 24, ncol = 3)
for (i in (1:dim(C)[1])) {
  C[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
  C[i,2] <- cos(i*pi/12 - pi/2)^500
  C[i,3] <- 1
}
Cres <- (solve(t(C)%*%C))%*%t(C)%*%c(avg_FL_2003, avg_FL_2004)
Cnew_res <- rep(0,12)
for (i in (1:length(Cnew_res))) {
  Cnew_res[i] <- Cres[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)) + Cres[2]*cos(i*pi/12 - pi/2)^500 + Cres[3]
}
Cmean_squared_error <- norm(C %*% Cres - avg_FL_2005, "2")

# Plot Florida
plot((1:12), avg_FL_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_FL_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.005), type = 'l')
plot((1:12), avg_FL_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
lines((1:12), Cnew_res, ylim = c(0,0.005))
par(col = "black")
plot((1:12), avg_FL_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
lines((1:12), Cnew_res, ylim = c(0,0.005))
par(col = "black")
plot((1:12), avg_FL_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
par(col = "red")
text((1:12), Cnew_res, ylim = c(0,0.005), labels = meses)
par(col = "black")
plot((1:12), avg_FL_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.005), type = 'l')
Axis(side=1, at = 1:12, labels = meses)

# # Experimento New York
# A <- matrix(nrow = 24, ncol = 2)
# for (i in (1:dim(A)[1])) {
#   A[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
#   A[i,2] <- 1
# }
# res <- (solve(t(A)%*%A))%*%t(A)%*%c(avg_NY_2003, avg_NY_2004)
# new_res <- rep(0,12)
# for (i in (1:length(new_res))) {
#   new_res[i] <- res[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2) + res[2]
# }
# mean_squared_error <- norm(A %*% res - avg_NY_2005, "2")
# 
# B <- matrix(nrow = 24, ncol = 3)
# for (i in (1:dim(B)[1])) {
#   B[i,1] <- sin(i*pi*2/12)
#   B[i,2] <- cos(i*pi*2/12)
#   B[i,3] <- 1
# }
# Bres <- (solve(t(B)%*%B))%*%t(B)%*%c(avg_NY_2003, avg_NY_2004)
# Bnew_res <- rep(0,12)
# for (i in (1:length(Bnew_res))) {
#   Bnew_res[i] <- Bres[1]*sin(i*pi*2/12) + Bres[2]*cos(i*pi*2/12) + Bres[3]
# }
# Bmean_squared_error <- norm(B %*% Bres - avg_NY_2005, "2")
# 
# C <- matrix(nrow = 24, ncol = 3)
# for (i in (1:dim(C)[1])) {
#   C[i,1] <- abs(sin(i*pi*2/24) * cos(i*pi*2/12)^2)
#   C[i,2] <- cos(i*pi/12 - pi/2)^500
#   C[i,3] <- 1
# }
# Cres <- (solve(t(C)%*%C))%*%t(C)%*%c(avg_NY_2003, avg_NY_2004)
# Cnew_res <- rep(0,12)
# for (i in (1:length(Cnew_res))) {
#   Cnew_res[i] <- Cres[1]*abs(sin(i*pi*2/24) * cos(i*pi*2/12)) + Cres[2]*cos(i*pi/12 - pi/2)^500 + Cres[3]
# }
# Cmean_squared_error <- norm(C %*% Cres - avg_NY_2005, "2")
# 
# # Plot New York
# plot((1:12), avg_NY_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_NY_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# # plot((1:12), avg_NY_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.008), type = 'l')
# plot((1:12), avg_NY_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_NY_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# par(col = "red")
# lines((1:12), Bnew_res, ylim = c(0,0.008))
# par(col = "black")
# plot((1:12), avg_NY_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# par(col = "red")
# lines((1:12), Bnew_res, ylim = c(0,0.008))
# par(col = "black")
# plot((1:12), avg_NY_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# par(col = "red")
# text((1:12), Bnew_res, ylim = c(0,0.008), labels = meses)
# par(col = "black")
# plot((1:12), avg_NY_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_NY_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_NY_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
# Axis(side=1, at = 1:12, labels = meses)

# Escribir en archivos
write(avg_CA_2000, "outputR/avg_CA_2000.in", ncolumns = 1)
write(avg_FL_2000, "outputR/avg_FL_2000.in", ncolumns = 1)
# write(avg_NY_2000, "outputR/avg_NY_2000.in", ncolumns = 1)
write(avg_CA_2001, "outputR/avg_CA_2001.in", ncolumns = 1)
write(avg_FL_2001, "outputR/avg_FL_2001.in", ncolumns = 1)
# write(avg_NY_2001, "outputR/avg_NY_2001.in", ncolumns = 1)
write(avg_CA_2002, "outputR/avg_CA_2002.in", ncolumns = 1)
write(avg_FL_2002, "outputR/avg_FL_2002.in", ncolumns = 1)
# write(avg_NY_2002, "outputR/avg_NY_2002.in", ncolumns = 1)
write(avg_CA_2003, "outputR/avg_CA_2003.in", ncolumns = 1)
write(avg_FL_2003, "outputR/avg_FL_2003.in", ncolumns = 1)
# write(avg_NY_2003, "outputR/avg_NY_2003.in", ncolumns = 1)
write(avg_CA_2004, "outputR/avg_CA_2004.in", ncolumns = 1)
write(avg_FL_2004, "outputR/avg_FL_2004.in", ncolumns = 1)
# write(avg_NY_2004, "outputR/avg_NY_2004.in", ncolumns = 1)
write(avg_CA_2005, "outputR/avg_CA_2005.in", ncolumns = 1)
write(avg_FL_2005, "outputR/avg_FL_2005.in", ncolumns = 1)
# write(avg_NY_2005, "outputR/avg_NY_2005.in", ncolumns = 1)
write(avg_CA_2006, "outputR/avg_CA_2006.in", ncolumns = 1)
write(avg_FL_2006, "outputR/avg_FL_2006.in", ncolumns = 1)
# write(avg_NY_2006, "outputR/avg_NY_2006.in", ncolumns = 1)
write(avg_CA_2007, "outputR/avg_CA_2007.in", ncolumns = 1)
write(avg_FL_2007, "outputR/avg_FL_2007.in", ncolumns = 1)
# write(avg_NY_2007, "outputR/avg_NY_2007.in", ncolumns = 1)
write(avg_CA_2008, "outputR/avg_CA_2008.in", ncolumns = 1)
write(avg_FL_2008, "outputR/avg_FL_2008.in", ncolumns = 1)
# write(avg_NY_2008, "outputR/avg_NY_2008.in", ncolumns = 1)

# O bien, hacer las querys
total_CA_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='CA' group by month")
total_FL_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='FL' group by month")
# total_NY_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='NY' group by month")
total_CA_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='CA' group by month")
total_FL_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='FL' group by month")
# total_NY_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='NY' group by month")
total_CA_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='CA' group by month")
total_FL_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='FL' group by month")
# total_NY_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='NY' group by month")
total_CA_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='CA' group by month")
total_FL_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='FL' group by month")
# total_NY_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='NY' group by month")
total_CA_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='CA' group by month")
total_FL_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='FL' group by month")
# total_NY_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='NY' group by month")
total_CA_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='CA' group by month")
total_FL_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='FL' group by month")
# total_NY_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='NY' group by month")
total_CA_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='CA' group by month")
total_FL_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='FL' group by month")
# total_NY_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='NY' group by month")
total_CA_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='CA' group by month")
total_FL_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='FL' group by month")
# total_NY_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='NY' group by month")
total_CA_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='CA' group by month")
total_FL_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='FL' group by month")
# total_NY_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='NY' group by month")

diverted_CA_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='NY' and diverted=1 group by month")
diverted_CA_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='FL' and diverted=1 group by month")
# diverted_NY_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='NY' and diverted=1 group by month")

avg_CA_2000 <- rep(0,12)
avg_FL_2000 <- rep(0,12)
# avg_NY_2000 <- rep(0,12)
avg_CA_2001 <- rep(0,12)
avg_FL_2001 <- rep(0,12)
# avg_NY_2001 <- rep(0,12)
avg_CA_2002 <- rep(0,12)
avg_FL_2002 <- rep(0,12)
# avg_NY_2002 <- rep(0,12)
avg_CA_2003 <- rep(0,12)
avg_FL_2003 <- rep(0,12)
# avg_NY_2003 <- rep(0,12)
avg_CA_2004 <- rep(0,12)
avg_FL_2004 <- rep(0,12)
# avg_NY_2004 <- rep(0,12)
avg_CA_2005 <- rep(0,12)
avg_FL_2005 <- rep(0,12)
# avg_NY_2005 <- rep(0,12)
avg_CA_2006 <- rep(0,12)
avg_FL_2006 <- rep(0,12)
# avg_NY_2006 <- rep(0,12)
avg_CA_2007 <- rep(0,12)
avg_FL_2007 <- rep(0,12)
# avg_NY_2007 <- rep(0,12)
avg_CA_2008 <- rep(0,12)
avg_FL_2008 <- rep(0,12)
# avg_NY_2008 <- rep(0,12)

for (i in (1:12)) {
  avg_CA_2000[i] = diverted_CA_2000$Count[i] / total_CA_2000$Count[i]
  avg_FL_2000[i] = diverted_FL_2000$Count[i] / total_FL_2000$Count[i]
  # avg_NY_2000[i] = diverted_NY_2000$Count[i] / total_NY_2000$Count[i]
  avg_CA_2001[i] = diverted_CA_2001$Count[i] / total_CA_2001$Count[i]
  avg_FL_2001[i] = diverted_FL_2001$Count[i] / total_FL_2001$Count[i]
  # avg_NY_2001[i] = diverted_NY_2001$Count[i] / total_NY_2001$Count[i]
  avg_CA_2002[i] = diverted_CA_2002$Count[i] / total_CA_2002$Count[i]
  avg_FL_2002[i] = diverted_FL_2002$Count[i] / total_FL_2002$Count[i]
  # avg_NY_2002[i] = diverted_NY_2002$Count[i] / total_NY_2002$Count[i]
  avg_CA_2003[i] = diverted_CA_2003$Count[i] / total_CA_2003$Count[i]
  avg_FL_2003[i] = diverted_FL_2003$Count[i] / total_FL_2003$Count[i]
  # avg_NY_2003[i] = diverted_NY_2003$Count[i] / total_NY_2003$Count[i]
  avg_CA_2004[i] = diverted_CA_2004$Count[i] / total_CA_2004$Count[i]
  avg_FL_2004[i] = diverted_FL_2004$Count[i] / total_FL_2004$Count[i]
  # avg_NY_2004[i] = diverted_NY_2004$Count[i] / total_NY_2004$Count[i]
  avg_CA_2005[i] = diverted_CA_2005$Count[i] / total_CA_2005$Count[i]
  avg_FL_2005[i] = diverted_FL_2005$Count[i] / total_FL_2005$Count[i]
  # avg_NY_2005[i] = diverted_NY_2005$Count[i] / total_NY_2005$Count[i]
  avg_CA_2006[i] = diverted_CA_2006$Count[i] / total_CA_2006$Count[i]
  avg_FL_2006[i] = diverted_FL_2006$Count[i] / total_FL_2006$Count[i]
  # avg_NY_2006[i] = diverted_NY_2006$Count[i] / total_NY_2006$Count[i]
  avg_CA_2007[i] = diverted_CA_2007$Count[i] / total_CA_2007$Count[i]
  avg_FL_2007[i] = diverted_FL_2007$Count[i] / total_FL_2007$Count[i]
  # avg_NY_2007[i] = diverted_NY_2007$Count[i] / total_NY_2007$Count[i]
  avg_CA_2008[i] = diverted_CA_2008$Count[i] / total_CA_2008$Count[i]
  avg_FL_2008[i] = diverted_FL_2008$Count[i] / total_FL_2008$Count[i]
  # avg_NY_2008[i] = diverted_NY_2008$Count[i] / total_NY_2008$Count[i]
}
