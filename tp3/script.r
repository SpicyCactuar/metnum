load_library <- function(){
  library(RSQLite)
  library(DBI)
  library(ggplot2)
}
load_library()
from_db <- function(sql) {
  dbGetQuery(ontime, sql)
}
ontime <- dbConnect(RSQLite::SQLite(), dbname = "ontime.sqlite3")

retrasados <- from_db("select count(*), origin from ontime2008 where depdelay > 15 group by origin order by origin")

retrasados_monthly <- from_db("select count(*) as Count, month, origin from ontime2008 where depdelay > 15 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2000 <- from_db("select count(*) as Count, month, origin from ontime2000 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2001 <- from_db("select count(*) as Count, month, origin from ontime2001 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2002 <- from_db("select count(*) as Count, month, origin from ontime2002 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2003 <- from_db("select count(*) as Count, month, origin from ontime2003 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2004 <- from_db("select count(*) as Count, month, origin from ontime2004 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2005 <- from_db("select count(*) as Count, month, origin from ontime2005 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2006 <- from_db("select count(*) as Count, month, origin from ontime2006 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2007 <- from_db("select count(*) as Count, month, origin from ontime2007 where cancelled = 1 group by origin, month order by origin, month")
retrasados_cancelled_monthly_2008 <- from_db("select count(*) as Count, month, origin from ontime2008 where cancelled = 1 group by origin, month order by origin, month")

plot(seq(1,length(retrasados$Count[retrasados$Count > 10000])), retrasados$Count[retrasados$Count > 10000])
text(seq(1,length(retrasados$Count[retrasados$Count > 10000])), retrasados$Count[retrasados$Count > 10000], labels=retrasados$Origin[retrasados$Count > 10000], cex= 0.7, pos = 3)

plot(retrasados_monthly$Month, retrasados_monthly$Count)
text(retrasados_monthly$Month, retrasados_monthly$Count, labels=retrasados_monthly$Origin, cex= 0.7, pos = 3)

meses <- c('E', 'F', 'M', 'A', 'M', 'J', 'J', 'A', 'S', 'O', 'N', 'D')

plot(retrasados_cancelled_monthly_2000$Month, retrasados_cancelled_monthly_2000$Count, axes = FALSE, xlab = '2000')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2001$Month, retrasados_cancelled_monthly_2001$Count, axes = FALSE, xlab = '2001')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2002$Month, retrasados_cancelled_monthly_2002$Count, axes = FALSE, xlab = '2002')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2003$Month, retrasados_cancelled_monthly_2003$Count, axes = FALSE, xlab = '2003')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2004$Month, retrasados_cancelled_monthly_2004$Count, axes = FALSE, xlab = '2004')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2005$Month, retrasados_cancelled_monthly_2005$Count, axes = FALSE, xlab = '2005')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2006$Month, retrasados_cancelled_monthly_2006$Count, axes = FALSE, xlab = '2006')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2007$Month, retrasados_cancelled_monthly_2007$Count, axes = FALSE, xlab = '2007')
Axis(side=1, at = 1:12, labels = meses)
plot(retrasados_cancelled_monthly_2008$Month, retrasados_cancelled_monthly_2008$Count, axes = FALSE, xlab = '2008')
Axis(side=1, at = 1:12, labels = meses)

text(retrasados_cancelled_monthly_2008$Month, retrasados_cancelled_monthly_2008$Count, labels=retrasados_cancelled_monthly_2008$Origin, cex= 0.7, pos = 3)

from_2008 <- from_db("select ontime2008.* from airport join ontime2008 on iata=origin where state='NY'")
to_2008 <- from_db("select ontime2008.* from airport join ontime2008 on iata=dest where state='NY'")

layout(matrix(1:9,1,9))
par(mar = c(4,0,0,0))

ggplot(NULL, aes(Month, Count)) + geom_point(data = retrasados_cancelled_monthly_2007) + geom_step(data = retrasados_cancelled_monthly_2008)
ggplot(NULL, aes(v, p)) + geom_point(data = df1) + geom_step(data = df2)
