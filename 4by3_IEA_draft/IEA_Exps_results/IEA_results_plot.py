import numpy as np
import pylab as p
from scipy.signal import butter, lfilter, freqz
p.figure()
data_filtered=[]
filename = "./chirp_tautrack_linear_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_lrd=np.array(data_filtered)


filename = "./chirp_tautrack_dgmm_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_drd=np.array(data_filtered)




p.subplot(2,2,1)
p.plot(data_lrd[:,0], data_lrd[:,2]) 
#p.plot(data_lrd[:,0], data_lrd[:,2]) 
p.plot(data_lrd[:,0], data_lrd[:,4])
p.plot(data_drd[:,0], data_drd[:,4])
p.grid()
p.legend(["motor current_I*x","motor current_filtered"])
p.ylabel("Current [A]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)
p.xlim([0,160])







p.subplot(2,2,2)
#p.plot(data_f[:,0], data_f[:,4]*180/np.pi) ## measured deflection
p.grid()
p.legend(["deflection"])
p.ylabel("Def [deg]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)

p.subplot(2,2,3)
#p.plot(data_f[:,0], data_f[:,4]*180/np.pi) ## measured velocity
p.grid()
p.legend(["velocity"])
p.ylabel("Vel [deg/s]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)

p.subplot(2,2,4)
#p.plot(data_f[:,0], data_f[:,1],'b+') ## measured velocity
p.grid()
p.legend(["tau_meas (sensor)"])
p.ylim([-20,20])
p.ylabel("Torque [Nm]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)

#p.suptitle("4by3_springmodeling_15092016_Exp%d"%exp_idx)
#p.savefig("./img/4by3_springmodeling_25102016_filtered_in34.8_pos4%d_v50.png"%exp_idx)
p.show()
p.close("all")		

