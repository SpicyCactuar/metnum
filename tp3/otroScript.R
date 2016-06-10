load_library <- function(){
  library(DBI)
  library(ggplot2)
}
load_library()
from_db <- function(sql) {
  dbGetQuery(ontime, sql)
}
ontime <- dbConnect(RSQLite::SQLite(), dbname = "ontime.sqlite3")

# Que estados vamos a usar
data <- from_db("select state, count(*) as Count from ontime2008 join airport on iata=dest group by state order by Count")

total_CA_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='CA' group by month")
total_FL_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='FL' group by month")
total_CA_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='CA' group by month")
total_FL_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='FL' group by month")
total_CA_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='CA' group by month")
total_FL_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='FL' group by month")
total_CA_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='CA' group by month")
total_FL_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='FL' group by month")
total_CA_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='CA' group by month")
total_FL_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='FL' group by month")
total_CA_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='CA' group by month")
total_FL_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='FL' group by month")
total_CA_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='CA' group by month")
total_FL_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='FL' group by month")
total_CA_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='CA' group by month")
total_FL_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='FL' group by month")
total_CA_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='CA' group by month")
total_FL_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='FL' group by month")

diverted_CA_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2000 <- from_db("select count(*) as Count from ontime2000 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2001 <- from_db("select count(*) as Count from ontime2001 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2002 <- from_db("select count(*) as Count from ontime2002 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2003 <- from_db("select count(*) as Count from ontime2003 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2004 <- from_db("select count(*) as Count from ontime2004 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2005 <- from_db("select count(*) as Count from ontime2005 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2006 <- from_db("select count(*) as Count from ontime2006 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2007 <- from_db("select count(*) as Count from ontime2007 join airport on iata=dest where state='FL' and diverted=1 group by month")
diverted_CA_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='CA' and diverted=1 group by month")
diverted_FL_2008 <- from_db("select count(*) as Count from ontime2008 join airport on iata=dest where state='FL' and diverted=1 group by month")

avg_CA_2000 <- rep(0,12)
avg_FL_2000 <- rep(0,12)
avg_CA_2001 <- rep(0,12)
avg_FL_2001 <- rep(0,12)
avg_CA_2002 <- rep(0,12)
avg_FL_2002 <- rep(0,12)
avg_CA_2003 <- rep(0,12)
avg_FL_2003 <- rep(0,12)
avg_CA_2004 <- rep(0,12)
avg_FL_2004 <- rep(0,12)
avg_CA_2005 <- rep(0,12)
avg_FL_2005 <- rep(0,12)
avg_CA_2006 <- rep(0,12)
avg_FL_2006 <- rep(0,12)
avg_CA_2007 <- rep(0,12)
avg_FL_2007 <- rep(0,12)
avg_CA_2008 <- rep(0,12)
avg_FL_2008 <- rep(0,12)

for (i in (1:12)) {
    avg_CA_2000[i] = diverted_CA_2000$Count[i] / total_CA_2000$Count[i]
    avg_FL_2000[i] = diverted_FL_2000$Count[i] / total_FL_2000$Count[i]
    avg_CA_2001[i] = diverted_CA_2001$Count[i] / total_CA_2001$Count[i]
    avg_FL_2001[i] = diverted_FL_2001$Count[i] / total_FL_2001$Count[i]
    avg_CA_2002[i] = diverted_CA_2002$Count[i] / total_CA_2002$Count[i]
    avg_FL_2002[i] = diverted_FL_2002$Count[i] / total_FL_2002$Count[i]
    avg_CA_2003[i] = diverted_CA_2003$Count[i] / total_CA_2003$Count[i]
    avg_FL_2003[i] = diverted_FL_2003$Count[i] / total_FL_2003$Count[i]
    avg_CA_2004[i] = diverted_CA_2004$Count[i] / total_CA_2004$Count[i]
    avg_FL_2004[i] = diverted_FL_2004$Count[i] / total_FL_2004$Count[i]
    avg_CA_2005[i] = diverted_CA_2005$Count[i] / total_CA_2005$Count[i]
    avg_FL_2005[i] = diverted_FL_2005$Count[i] / total_FL_2005$Count[i]
    avg_CA_2006[i] = diverted_CA_2006$Count[i] / total_CA_2006$Count[i]
    avg_FL_2006[i] = diverted_FL_2006$Count[i] / total_FL_2006$Count[i]
    avg_CA_2007[i] = diverted_CA_2007$Count[i] / total_CA_2007$Count[i]
    avg_FL_2007[i] = diverted_FL_2007$Count[i] / total_FL_2007$Count[i]
    avg_CA_2008[i] = diverted_CA_2008$Count[i] / total_CA_2008$Count[i]
    avg_FL_2008[i] = diverted_FL_2008$Count[i] / total_FL_2008$Count[i]
}

meses <- c('E', 'F', 'M', 'A', 'M', 'J', 'J', 'A', 'S', 'O', 'N', 'D')

layout(matrix(0:9,1,10), widths = c(1,rep(4, 9)))
par(mar = c(4,0,0,0))
# layout(matrix(0:7,1,8), widths = c(1,rep(4, 9)))
# par(mar = c(4,0,0,0))

plot((1:12), avg_CA_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_CA_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.008), type = 'l')
plot((1:12), avg_CA_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_CA_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)

plot((1:12), avg_FL_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
# plot((1:12), avg_FL_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.008), type = 'l')
plot((1:12), avg_FL_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot((1:12), avg_FL_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.008), type = 'l')
Axis(side=1, at = 1:12, labels = meses)

A <- matrix(nrow = 12, ncol = 2, data = 1)

for (i in (1:dim(A)[1])) {
  A[i][1] <- avg_FL_2003[i]
  A[i][2] <- 1
}

res <- lsfit(A, avg_FL_2003)

write(avg_CA_2000, "outputR/avg_CA_2000.in", ncolumns = 1)
write(avg_FL_2000, "outputR/avg_FL_2000.in", ncolumns = 1)
write(avg_CA_2001, "outputR/avg_CA_2001.in", ncolumns = 1)
write(avg_FL_2001, "outputR/avg_FL_2001.in", ncolumns = 1)
write(avg_CA_2002, "outputR/avg_CA_2002.in", ncolumns = 1)
write(avg_FL_2002, "outputR/avg_FL_2002.in", ncolumns = 1)
write(avg_CA_2003, "outputR/avg_CA_2003.in", ncolumns = 1)
write(avg_FL_2003, "outputR/avg_FL_2003.in", ncolumns = 1)
write(avg_CA_2004, "outputR/avg_CA_2004.in", ncolumns = 1)
write(avg_FL_2004, "outputR/avg_FL_2004.in", ncolumns = 1)
write(avg_CA_2005, "outputR/avg_CA_2005.in", ncolumns = 1)
write(avg_FL_2005, "outputR/avg_FL_2005.in", ncolumns = 1)
write(avg_CA_2006, "outputR/avg_CA_2006.in", ncolumns = 1)
write(avg_FL_2006, "outputR/avg_FL_2006.in", ncolumns = 1)
write(avg_CA_2007, "outputR/avg_CA_2007.in", ncolumns = 1)
write(avg_FL_2007, "outputR/avg_FL_2007.in", ncolumns = 1)
write(avg_CA_2008, "outputR/avg_CA_2008.in", ncolumns = 1)
write(avg_FL_2008, "outputR/avg_FL_2008.in", ncolumns = 1)
