import numpy as np
import pylab as p
from scipy.signal import butter, lfilter, freqz
p.figure()
data_filtered=[]
filename = "./chirp_tautrack_linear_taucmd_trained_incl30_02.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<5 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_lc=np.array(data_filtered)


filename = "./chirp_tautrack_dgmm_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_dc=np.array(data_filtered)

for i in range(5,len(data_dc[:,0])):
        data_dc[i,1]=data_lc[i-3:i+3,1].mean()
        data_lc[i,1]=data_lc[i-3:i+3,1].mean()

p.subplot(2,2,1)
p.plot(data_lc[:,0], data_lc[:,2], 'k-', label='desired', linewidth=2.0) 
p.plot(data_dc[:,0], data_dc[:,1], 'r-', label='DGMM', linewidth=2.0)
p.plot(data_lc[:,0], data_lc[:,1], 'g-', label='linear', linewidth=2.0)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.05))
p.ylabel("Current [A]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)
p.xlim([0,160])


p.subplot(2,2,3)
p.plot(data_dc[:,0], abs(data_dc[:,1]-data_dc[:,2]), 'r-', label='tracking errorc(DGMM)', linewidth=1.0)
p.plot(data_lc[:,0], abs(data_lc[:,1]-data_lc[:,2]), 'g-', label='tracking errorc(linear)', linewidth=1.0)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.05))
p.ylabel("Def [deg]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)
p.xlim([0,160])

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  random walk    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data_filtered=[]
filename = "./randomwalk_tautrack_linear_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<5 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_lrd=np.array(data_filtered)


filename = "./randomwalk_tautrack_dgmm_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_drd=np.array(data_filtered)

for i in range(5,len(data_drd[:,0])):
        data_drd[i,1]=data_drd[i-3:i+3,1].mean()
        data_lrd[i,1]=data_lrd[i-3:i+3,1].mean()



p.subplot(2,2,2)
#p.plot(data_lrd[:,0], data_lrd[:,2], 'k-', label='desired', linewidth=2.0) 
#p.plot(data_drd[:,0], data_drd[:,1], 'r-', label='DGMM', linewidth=2.0)
#p.plot(data_lrd[:,0], data_lrd[:,1], 'g-', label='linear', linewidth=2.0)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.05))
p.ylabel("Current [A]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)
p.xlim([0,160])


p.subplot(2,2,4)
#p.plot(data_drd[:,0], abs(data_drd[:,1]-data_drd[:,2]), 'r-', label='tracking errorc(DGMM)', linewidth=1.0)
#p.plot(data_lrd[:,0], abs(data_lrd[:,1]-data_lrd[:,2]), 'g-', label='tracking errorc(linear)', linewidth=1.0)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.05))
p.ylabel("Def [deg]", fontsize=20)
p.xlabel("Time[s]", fontsize=20)
p.xlim([0,160])


#p.suptitle("4by3_springmodeling_15092016_Exp%d"%exp_idx)
#p.savefig("./img/4by3_springmodeling_25102016_filtered_in34.8_pos4%d_v50.png"%exp_idx)
p.show()
p.close("all")		

