import numpy as np
import pylab as p
import sys
from scipy.optimize import curve_fit
from dgmm_spherical import dgmm_spherical
filename = "./real_test/data_train.csv"
dat = np.recfromcsv(filename, names=True, skip_header=0, dtype=np.float)[::5]
dgmm_size_limit=3000
dgmm = dgmm_spherical()
dgmm.init_cov(0.01)
data_dgmm=[]


for i in range(1,len(dat["time"])):
    if abs(dat["tau_sensor"][i]-dat["tau_mod"][i])<4 and 0.00001<abs(dat["tau_sensor"][i])<25: # remove the error sample of the torque measurement
        ob_vec=[dat["time"][i],dat["q_spring_meas"][i],dat["tau_sensor"][i],dat["dq_meas"][i],dat["q_spring_meas"][i-1]] 
        observation_vector=np.array([np.concatenate(([dat["q_spring_meas"][i]],[dat["tau_sensor"][i]],[dat["dq_meas"][i]],[dat["q_spring_meas"][i-1]]), axis=0)]).T
        data_dgmm.append(np.array(ob_vec))
        dgmm.update_online_nov_kmeans(observation_vector,0.08)
        #dgmm.update_online_kmeans(observation_vector,dgmm_size_limit)  ## use online kmeans method to train the dgmm
dgmm.SaveModel("./dgmm_model_track_20112016")  ##save the dgmm model

data_dgmm=np.array(data_dgmm)
np.savetxt("./data_dgmm.csv",data_dgmm, delimiter= ",")  
data_dgmm=np.genfromtxt(open("./data_dgmm.csv", "rb"), delimiter=',') 

#for i in range(5,len(data_dgmm[:,0])):
#    data_dgmm[i,1]=data_dgmm[i-3:i+3,1].mean()

p.figure(1)
p.rcParams['font.size'] = 16
p.subplot(311)
p.plot(data_dgmm[:,0], data_dgmm[:,2],'r-', lw=3.5,label='mod')
#p.plot(data_linear[:,0], data_linear[:,2],'r-', lw=3.5,label='desired')
p.plot(data_dgmm[:,0], data_dgmm[:,1],'b-', lw=2.5,label='sensor')
#p.plot(data_linear[:,0], data_linear[:,1],'g-', lw=2, alpha=0.9,label='linear')

#p.plot(data_linear2[:,0]-45.7, data_linear2[:,1],'--', lw=2)
p.grid()
#p.legend(["Tau_ref","Tau_meas(DGMM)","Tau_meas(Linear)"])
#p.legend(["Desired","DGMM","Linear"])
p.legend(bbox_to_anchor=(1, 1.5))
p.ylim([-25,25])
p.xlim([0,500])
p.ylabel("Torque (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)

p.subplot(312)
p.plot(data_dgmm[:,0], abs(data_dgmm[:,2]-data_dgmm[:,1]),'r-', lw=2.5,label='tracking error (DGMM)')
#p.plot(data_linear[:,0]-45.7, data_linear[:,2]-data_linear[:,1],'g-', lw=1.5,label='Tracking error(Linear)')
#p.plot(data_linear[:,0], abs(data_linear[:,2]-data_linear[:,1]),'g-', lw=1.5, alpha=0.9,label='tracking error (linear)')
p.grid()
p.legend(bbox_to_anchor=(1.07, 1.5))
p.ylim([0,15])
p.xlim([0,500])
p.ylabel("Torque err(or (Nm)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)


p.subplot(313)
#p.plot(data_dgmm[:,0], data_dgmm[:,2],'r-', lw=3.5,label='desired')
#p.plot(data_linear[:,0], data_linear[:,4],'r-', lw=3.5,label='linear')
p.plot(data_dgmm[:,0], data_dgmm[:,2]*180/np.pi,'b-', lw=2.5,label='DGMM')
#p.plot(data_linear[:,0], data_linear[:,1],'g-', lw=2, alpha=0.9,label='linear')
p.grid()
p.legend(bbox_to_anchor=(1, 1.5))
#p.ylim([0,8])
p.xlim([0,500])
p.ylabel("Velocity (rad/s)", fontsize=20)
p.xlabel("Time (s)", fontsize=20)
p.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=None, hspace=.8)
p.show()
p.close("all")















