import numpy as np
import pylab as p
from scipy.signal import butter, lfilter, freqz
p.figure()
p.rcParams.update({'font.size': 16})
data_filtered=[]
filename = "./linear_results/chirp_tautrack_linear_taucmd_trained_incl30_02.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<5 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_lchirp=np.array(data_filtered)


filename = "./dgmm_results/chirp_tautrack_dgmm_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_dchirp=np.array(data_filtered)

filename = "./NN_results_14122016/chirp_NN_14122016_new_result_exp03.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<3 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_nchirp=np.array(data_filtered)

fl=5
for i in range(fl,len(data_lchirp[:,0])):
        data_lchirp[i,1]=data_lchirp[i-fl:i+fl,1].mean()
fl=10
for i in range(fl,len(data_dchirp[:,0])):
        data_dchirp[i,1]=data_dchirp[i-fl:i+fl,1].mean()
        data_nchirp[i,1]=data_nchirp[i-fl:i+fl,1].mean()

p.subplot(2,2,1)
p.plot(data_lchirp[:,0], data_lchirp[:,2], 'g--', label='desired', linewidth=3) 
p.plot(data_nchirp[:,0], data_nchirp[:,1], 'y-', label='NN', linewidth=2.5,alpha=0.8)
p.plot(data_dchirp[:,0], data_dchirp[:,1], 'r-', label='DGMM', linewidth=2,alpha=1)
p.plot(data_lchirp[:,0], data_lchirp[:,1], 'b-', label='linear', linewidth=2,alpha=1)
p.grid()
p.legend(bbox_to_anchor=(1.05, 1.3))
p.ylabel("Torque (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)
p.xlim([0,160])


p.subplot(2,2,3)
p.plot(data_nchirp[:,0], abs(data_nchirp[:,1]-data_nchirp[:,2]), 'y-', label='tracking error (NN)', linewidth=1.5)
p.plot(data_dchirp[:,0], abs(data_dchirp[:,1]-data_dchirp[:,2]), 'r-', label='tracking error (DGMM)', linewidth=1.5)
p.plot(data_lchirp[:,0], abs(data_lchirp[:,1]-data_lchirp[:,2]), 'b-', label='tracking error (linear)', linewidth=1.5)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.2))
p.ylabel("Torque error (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)
p.xlim([0,160])




filename = "./linear_results/randomwalk_tautrack_linear_taucmd_trained_incl30_01.csv"
dat3 = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat3["time"])):
    if abs(dat3["tau_sensor"][i]-dat3["tau_ref_traj"][i])<5 and 0.00001<abs(dat3["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat3["time"][i],dat3["tau_sensor"][i], dat3["tau_ref_traj"][i],dat3["q_spring_meas"][i], dat3["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_lrd=np.array(data_filtered)


filename = "./dgmm_results/randomwalk_tautrack_dgmm_taucmd_trained_incl30_01.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<5 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_drd=np.array(data_filtered)

filename = "./NN_results_14122016/randomwalk_NN_14122016_new_result_exp03.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)
data_filtered=[]
for i in range(5,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_ref_traj"][i])<5 and 0.00001<abs(dat["tau_sensor"][i])<20: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["tau_sensor"][i], dat["tau_ref_traj"][i],dat["q_spring_meas"][i], dat["tau_mod"][i]]
        data_filtered.append(np.array(ob_vec))
data_nrd=np.array(data_filtered)

p.subplot(2,2,2)
p.plot(data_lrd[:,0], data_lrd[:,2], 'g-', label='desired', linewidth=3.0) 
p.plot(data_nrd[:,0], data_nrd[:,4], 'y-', label='NN', linewidth=2.5,alpha=0.8)
p.plot(data_drd[:,0], data_drd[:,4], 'r-', label='DGMM', linewidth=2,alpha=1)
p.plot(data_lrd[:,0], data_lrd[:,4], 'b-', label='linear', linewidth=2,alpha=1)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.3))
p.ylabel("Torque (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)
p.xlim([0,160])
p.ylim([-15,19])

p.subplot(2,2,4)
p.plot(data_nrd[:,0], abs(data_nrd[:,4]-data_nrd[:,2]), 'y+', label='tracking error (NN)', linewidth=1.0, markersize=3)
p.plot(data_drd[:,0], abs(data_drd[:,4]-data_drd[:,2]), 'r+', label='tracking error (DGMM)', linewidth=1.0, markersize=3)
p.plot(data_lrd[:,0], abs(data_lrd[:,4]-data_lrd[:,2]), 'b+', label='tracking error (linear)', linewidth=1.0, markersize=3)
p.grid()
p.legend(bbox_to_anchor=(1.1, 1.2))
p.ylabel("Torque error (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)
p.xlim([0,160])
p.ylim([0,6])

#p.suptitle("4by3_springmodeling_15092016_Exp%d"%exp_idx)
#p.savefig("./img/4by3_springmodeling_25102016_filtered_in34.8_pos4%d_v50.png"%exp_idx)
p.subplots_adjust(wspace=.2, hspace=.4)
p.show()
p.close("all")		

