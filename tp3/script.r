load_library <- function(){
  library(DBI)
  library(ggplot2)
}
load_library()
from_db <- function(sql) {
  dbGetQuery(ontime, sql)
}
ontime <- dbConnect(RSQLite::SQLite(), dbname = "ontime.sqlite3")

meses <- c('E', 'F', 'M', 'A', 'M', 'J', 'J', 'A', 'S', 'O', 'N', 'D')

delayed_monthly_2000 <- from_db("select count(*) as Count, month from ontime2000 where depdelay > 15 group by month order by month")
delayed_monthly_2001 <- from_db("select count(*) as Count, month from ontime2001 where depdelay > 15 group by month order by month")
delayed_monthly_2002 <- from_db("select count(*) as Count, month from ontime2002 where depdelay > 15 group by month order by month")
delayed_monthly_2003 <- from_db("select count(*) as Count, month from ontime2003 where depdelay > 15 group by month order by month")
delayed_monthly_2004 <- from_db("select count(*) as Count, month from ontime2004 where depdelay > 15 group by month order by month")
delayed_monthly_2005 <- from_db("select count(*) as Count, month from ontime2005 where depdelay > 15 group by month order by month")
delayed_monthly_2006 <- from_db("select count(*) as Count, month from ontime2006 where depdelay > 15 group by month order by month")
delayed_monthly_2007 <- from_db("select count(*) as Count, month from ontime2007 where depdelay > 15 group by month order by month")
delayed_monthly_2008 <- from_db("select count(*) as Count, month from ontime2008 where depdelay > 15 group by month order by month")

total_delayed_monthly_2000 <- from_db("select count(*) as Count, month from ontime2000 group by month order by month")
total_delayed_monthly_2001 <- from_db("select count(*) as Count, month from ontime2001 group by month order by month")
total_delayed_monthly_2002 <- from_db("select count(*) as Count, month from ontime2002 group by month order by month")
total_delayed_monthly_2003 <- from_db("select count(*) as Count, month from ontime2003 group by month order by month")
total_delayed_monthly_2004 <- from_db("select count(*) as Count, month from ontime2004 group by month order by month")
total_delayed_monthly_2005 <- from_db("select count(*) as Count, month from ontime2005 group by month order by month")
total_delayed_monthly_2006 <- from_db("select count(*) as Count, month from ontime2006 group by month order by month")
total_delayed_monthly_2007 <- from_db("select count(*) as Count, month from ontime2007 group by month order by month")
total_delayed_monthly_2008 <- from_db("select count(*) as Count, month from ontime2008 group by month order by month")

averages_2000 <- c(rep(0,12))
averages_2001 <- c(rep(0,12))
averages_2002 <- c(rep(0,12))
averages_2003 <- c(rep(0,12))
averages_2004 <- c(rep(0,12))
averages_2005 <- c(rep(0,12))
averages_2006 <- c(rep(0,12))
averages_2007 <- c(rep(0,12))
averages_2008 <- c(rep(0,12))

for (i in 1:12) {
  averages_2000[i] = delayed_monthly_2000$Count[i] / total_delayed_monthly_2000$Count[i]
  averages_2001[i] = delayed_monthly_2001$Count[i] / total_delayed_monthly_2001$Count[i]
  averages_2002[i] = delayed_monthly_2002$Count[i] / total_delayed_monthly_2002$Count[i]
  averages_2003[i] = delayed_monthly_2003$Count[i] / total_delayed_monthly_2003$Count[i]
  averages_2004[i] = delayed_monthly_2004$Count[i] / total_delayed_monthly_2004$Count[i]
  averages_2005[i] = delayed_monthly_2005$Count[i] / total_delayed_monthly_2005$Count[i]
  averages_2006[i] = delayed_monthly_2006$Count[i] / total_delayed_monthly_2006$Count[i]
  averages_2007[i] = delayed_monthly_2007$Count[i] / total_delayed_monthly_2007$Count[i]
  averages_2008[i] = delayed_monthly_2008$Count[i] / total_delayed_monthly_2008$Count[i]
}

#layout(matrix(0:9,1,10), widths = c(1,rep(4, 9)))
#par(mar = c(4,0,0,0))
layout(matrix(0:7,1,8), widths = c(1,rep(4, 9)))
par(mar = c(4,0,0,0))

#plot(delayed_monthly_2000$Month, averages_2000, xlab = '2000', xaxt = 'n', ylim = c(0,0.5), type = 'l')
#Axis(side=1, at = 1:12, labels = meses)
#plot(delayed_monthly_2001$Month, averages_2001, xlab = '2001', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
#Axis(side=1, at = 1:12, labels = meses)

plot(delayed_monthly_2002$Month, averages_2002, xlab = '2002', xaxt = 'n', ylim = c(0,0.5), type = 'l')
#plot(delayed_monthly_2002$Month, averages_2002, xlab = '2002', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2003$Month, averages_2003, xlab = '2003', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2004$Month, averages_2004, xlab = '2004', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2005$Month, averages_2005, xlab = '2005', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2006$Month, averages_2006, xlab = '2006', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2007$Month, averages_2007, xlab = '2007', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)
plot(delayed_monthly_2008$Month, averages_2008, xlab = '2008', xaxt = 'n', yaxt = 'n', ylim = c(0,0.5), type = 'l')
Axis(side=1, at = 1:12, labels = meses)

A = matrix()

lsfit(, averages_2002)

cancelled_monthly_2000 <- from_db("select count(*) as Count, month from ontime2000 where cancelled = 1 group by month order by month")
cancelled_monthly_2001 <- from_db("select count(*) as Count, month from ontime2001 where cancelled = 1 group by month order by month")
cancelled_monthly_2002 <- from_db("select count(*) as Count, month from ontime2002 where cancelled = 1 group by month order by month")
cancelled_monthly_2003 <- from_db("select count(*) as Count, month from ontime2003 where cancelled = 1 group by month order by month")
cancelled_monthly_2004 <- from_db("select count(*) as Count, month from ontime2004 where cancelled = 1 group by month order by month")
cancelled_monthly_2005 <- from_db("select count(*) as Count, month from ontime2005 where cancelled = 1 group by month order by month")
cancelled_monthly_2006 <- from_db("select count(*) as Count, month from ontime2006 where cancelled = 1 group by month order by month")
cancelled_monthly_2007 <- from_db("select count(*) as Count, month from ontime2007 where cancelled = 1 group by month order by month")
cancelled_monthly_2008 <- from_db("select count(*) as Count, month from ontime2008 where cancelled = 1 group by month order by month")

plot(cancelled_monthly_2000$Month, cancelled_monthly_2000$Count, axes = FALSE, xlab = '2000')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2001$Month, cancelled_monthly_2001$Count, axes = FALSE, xlab = '2001')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2002$Month, cancelled_monthly_2002$Count, axes = FALSE, xlab = '2002')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2003$Month, cancelled_monthly_2003$Count, axes = FALSE, xlab = '2003')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2004$Month, cancelled_monthly_2004$Count, axes = FALSE, xlab = '2004')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2005$Month, cancelled_monthly_2005$Count, axes = FALSE, xlab = '2005')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2006$Month, cancelled_monthly_2006$Count, axes = FALSE, xlab = '2006')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2007$Month, cancelled_monthly_2007$Count, axes = FALSE, xlab = '2007')
Axis(side=1, at = 1:12, labels = meses)
plot(cancelled_monthly_2008$Month, cancelled_monthly_2008$Count, axes = FALSE, xlab = '2008')
Axis(side=1, at = 1:12, labels = meses)

from_2008 <- from_db("select ontime2008.* from airport join ontime2008 on iata=origin where state='NY'")
to_2008 <- from_db("select ontime2008.* from airport join ontime2008 on iata=dest where state='NY'")
