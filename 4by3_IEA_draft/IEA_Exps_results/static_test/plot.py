import numpy as np
import pylab as p
import sys
from scipy.optimize import curve_fit
filename = "./data_static2.csv"

if len(sys.argv) > 1:
  filename = sys.argv[1]
  
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)

p.figure()
p.rcParams.update({'font.size': 22})
p.subplot(2,2,1)
p.plot(dat["time"], dat["q_gear_meas"]*180.0/np.pi)
p.grid()
p.legend(["pos_meas"])
p.ylabel("pos [deg]")
p.xlabel("time[s]")


p.subplot(2,2,2)
p.plot(dat["time"], dat["dq_meas"])
p.grid()
p.legend(["vel_meas"])
p.ylabel("vel [rad/s]")
p.xlabel("time[s]")


p.subplot(2,2,3)
p.plot(dat["tau_sensor"], dat["q_spring_meas"]*180.0/np.pi,'+')
#p.plot(dat["time"], dat["t_ld"]*180.0/np.pi)
#p.plot(dat["q_spring_meas"]*180.0/np.pi, dat["tau_sensor"],'+')
#p.plot(dat["t_ld"], dat["tau_sensor"],'+')
p.grid()
p.legend(["def_meas","def_cmd"])
p.ylabel("current [A]")
p.xlabel("time[s]")


p.subplot(2,2,4)
#p.plot(dat["time"], dat["tau_ref_traj"],'+')
p.plot(dat["time"], dat["tau_sensor"],'+')
p.grid()
p.legend(["tau_ref","tau_meas"])
#p.ylim([-20,20])
p.ylabel("torque [Nm]")
p.xlabel("time[s]")
#np.where(np.logical_and(a>=6, a<=10))
p.show()
p.close("all")

