data_rand = read.csv("data_rand.csv") #FET
data_full = read.csv("data_full.csv") #FET
data_int = read.csv("data_40-60.csv") #FET

##################   TOTS ELS DESORDRES   ####################
##############################################################
tm_full = data_full$time_merge
tq_full = data_full$time_quick
des_full = data_full$inversiones
resta_full <- tm_full-tq_full

##################   DESORDRES RANDOM   ######################
##############################################################
tm_rand = data_rand$time_merge
tq_rand = data_rand$time_quick
des_rand = data_rand$inversiones
resta_rand <- tm_rand-tq_rand

#############   DESORDRES EN UN INTERVAL   ###################
##############################################################
tm_int = data_int$time_merge
tq_int = data_int$time_quick
des_int = data_int$inversiones
resta_int <- tm_int-tq_int

###################   GRAFIQUES   ############################
##############################################################

#Normal del desordre random
qqnorm(des_rand)
qqline(des_rand)

#Diferencia respecte tots els desordres
plot(des_full, resta_full)
abline(h = 0)

#Temps respecte el desordre dels dos algoritmes
plot(des_rand, tq_rand)
plot(des_rand, tm_rand)
#Difernecia en funció del desordre amb recte
plot(des_rand, resta_rand)
abline(lm(resta_rand~des_rand))

#Boxplot de la diferencia
boxplot(resta_rand)

#QQNorm de la resta
qqnorm(resta_rand)
qqline(resta_rand)

#T.Test dels temps
t.test(tm_rand, tq_rand, paried=T)

#Info de l'estudi de la diferencia amb el desordre
summary(lm(resta_rand~des_rand))

#install.packages("PairedData")
#library(PairedData)
#p <- paired(tm_rand,tq_rand)
#plot(p,type='BA')
#qqline(resta)

mean(tm_rand)
mean(tq_rand)
mean(resta_rand)

sd(tm_rand)
sd(tq_rand)
sd(resta_rand)