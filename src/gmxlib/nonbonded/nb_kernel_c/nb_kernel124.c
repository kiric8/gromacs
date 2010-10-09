/*
 * Copyright (c) Erik Lindahl, David van der Spoel 2003
 * 
 * This file is generated automatically at compile time
 * by the program mknb in the Gromacs distribution.
 *
 * Options used when generation this file:
 * Language:         c
 * Precision:        single
 * Threads:          no
 * Software invsqrt: no
 * PowerPC invsqrt:  no
 * Prefetch forces:  no
 * Comments:         no
 */
#ifdef HAVE_CONFIG_H
#include<config.h>
#endif
#include<math.h>
#include "types/simple.h"
#include "localpressure.h"



/*
 * Gromacs nonbonded kernel nb_kernel124
 * Coulomb interaction:     Normal Coulomb
 * VdW interaction:         Buckingham
 * water optimization:      pairs of TIP4P interactions
 * Calculate forces:        yes
 */
void nb_kernel124(
                    int *           p_nri,
                    int *           iinr,
                    int *           jindex,
                    int *           jjnr,
                    int *           shift,
                    real *          shiftvec,
                    real *          fshift,
                    int *           gid,
                    real *          pos,
                    real *          faction,
                    real *          charge,
                    real *          p_facel,
                    real *          p_krf,
                    real *          p_crf,
                    real *          Vc,
                    int *           type,
                    int *           p_ntype,
                    real *          vdwparam,
                    real *          Vvdw,
                    real *          p_tabscale,
                    real *          VFtab,
                    real *          invsqrta,
                    real *          dvda,
                    real *          p_gbtabscale,
                    real *          GBtab,
                    int *           p_nthreads,
                    int *           count,
                    void *          mtx,
                    int *           outeriter,
                    int *           inneriter,
                    real *          work)
{
      gmx_localp_grid_t * localp_grid = (gmx_localp_grid_t *)work;
    int           nri,ntype,nthreads;
    real          facel,krf,crf,tabscale,gbtabscale;
    int           n,ii,is3,ii3,k,nj0,nj1,jnr,j3,ggid;
    real          shX,shY,shZ;
    real          fscal,tx,ty,tz;
    real          rinvsq;
    real          qq,vcoul,vctot;
    int           tj;
    real          rinvsix;
    real          Vvdw6,Vvdwtot;
    real          Vvdwexp,br;
    real          ix1,iy1,iz1,fix1,fiy1,fiz1;
    real          ix2,iy2,iz2,fix2,fiy2,fiz2;
    real          ix3,iy3,iz3,fix3,fiy3,fiz3;
    real          ix4,iy4,iz4,fix4,fiy4,fiz4;
    real          jx1,jy1,jz1;
    real          jx2,jy2,jz2,fjx2,fjy2,fjz2;
    real          jx3,jy3,jz3,fjx3,fjy3,fjz3;
    real          jx4,jy4,jz4,fjx4,fjy4,fjz4;
    real          dx11,dy11,dz11,rsq11,rinv11;
    real          dx22,dy22,dz22,rsq22,rinv22;
    real          dx23,dy23,dz23,rsq23,rinv23;
    real          dx24,dy24,dz24,rsq24,rinv24;
    real          dx32,dy32,dz32,rsq32,rinv32;
    real          dx33,dy33,dz33,rsq33,rinv33;
    real          dx34,dy34,dz34,rsq34,rinv34;
    real          dx42,dy42,dz42,rsq42,rinv42;
    real          dx43,dy43,dz43,rsq43,rinv43;
    real          dx44,dy44,dz44,rsq44,rinv44;
    real          qH,qM,qqMM,qqMH,qqHH;
    real          c6,cexp1,cexp2;

    nri              = *p_nri;         
    ntype            = *p_ntype;       
    nthreads         = *p_nthreads;    
    facel            = *p_facel;       
    krf              = *p_krf;         
    crf              = *p_crf;         
    tabscale         = *p_tabscale;    
    ii               = iinr[0];        
    qH               = charge[ii+1];   
    qM               = charge[ii+3];   
    qqMM             = facel*qM*qM;    
    qqMH             = facel*qM*qH;    
    qqHH             = facel*qH*qH;    
    tj               = 3*(ntype+1)*type[ii];
    c6               = vdwparam[tj];   
    cexp1            = vdwparam[tj+1]; 
    cexp2            = vdwparam[tj+2]; 

    nj1              = 0;              
    
    for(n=0; (n<nri); n++)
    {
        is3              = 3*shift[n];     
        shX              = shiftvec[is3];  
        shY              = shiftvec[is3+1];
        shZ              = shiftvec[is3+2];
        nj0              = jindex[n];      
        nj1              = jindex[n+1];    
        ii               = iinr[n];        
        ii3              = 3*ii;           
        ix1              = shX + pos[ii3+0];
        iy1              = shY + pos[ii3+1];
        iz1              = shZ + pos[ii3+2];
        ix2              = shX + pos[ii3+3];
        iy2              = shY + pos[ii3+4];
        iz2              = shZ + pos[ii3+5];
        ix3              = shX + pos[ii3+6];
        iy3              = shY + pos[ii3+7];
        iz3              = shZ + pos[ii3+8];
        ix4              = shX + pos[ii3+9];
        iy4              = shY + pos[ii3+10];
        iz4              = shZ + pos[ii3+11];
        vctot            = 0;              
        Vvdwtot          = 0;              
        fix1             = 0;              
        fiy1             = 0;              
        fiz1             = 0;              
        fix2             = 0;              
        fiy2             = 0;              
        fiz2             = 0;              
        fix3             = 0;              
        fiy3             = 0;              
        fiz3             = 0;              
        fix4             = 0;              
        fiy4             = 0;              
        fiz4             = 0;              
        
        for(k=nj0; (k<nj1); k++)
        {
            jnr              = jjnr[k];        
            j3               = 3*jnr;          
            jx1              = pos[j3+0];      
            jy1              = pos[j3+1];      
            jz1              = pos[j3+2];      
            jx2              = pos[j3+3];      
            jy2              = pos[j3+4];      
            jz2              = pos[j3+5];      
            jx3              = pos[j3+6];      
            jy3              = pos[j3+7];      
            jz3              = pos[j3+8];      
            jx4              = pos[j3+9];      
            jy4              = pos[j3+10];     
            jz4              = pos[j3+11];     
            dx11             = ix1 - jx1;      
            dy11             = iy1 - jy1;      
            dz11             = iz1 - jz1;      
            rsq11            = dx11*dx11+dy11*dy11+dz11*dz11;
            dx22             = ix2 - jx2;      
            dy22             = iy2 - jy2;      
            dz22             = iz2 - jz2;      
            rsq22            = dx22*dx22+dy22*dy22+dz22*dz22;
            dx23             = ix2 - jx3;      
            dy23             = iy2 - jy3;      
            dz23             = iz2 - jz3;      
            rsq23            = dx23*dx23+dy23*dy23+dz23*dz23;
            dx24             = ix2 - jx4;      
            dy24             = iy2 - jy4;      
            dz24             = iz2 - jz4;      
            rsq24            = dx24*dx24+dy24*dy24+dz24*dz24;
            dx32             = ix3 - jx2;      
            dy32             = iy3 - jy2;      
            dz32             = iz3 - jz2;      
            rsq32            = dx32*dx32+dy32*dy32+dz32*dz32;
            dx33             = ix3 - jx3;      
            dy33             = iy3 - jy3;      
            dz33             = iz3 - jz3;      
            rsq33            = dx33*dx33+dy33*dy33+dz33*dz33;
            dx34             = ix3 - jx4;      
            dy34             = iy3 - jy4;      
            dz34             = iz3 - jz4;      
            rsq34            = dx34*dx34+dy34*dy34+dz34*dz34;
            dx42             = ix4 - jx2;      
            dy42             = iy4 - jy2;      
            dz42             = iz4 - jz2;      
            rsq42            = dx42*dx42+dy42*dy42+dz42*dz42;
            dx43             = ix4 - jx3;      
            dy43             = iy4 - jy3;      
            dz43             = iz4 - jz3;      
            rsq43            = dx43*dx43+dy43*dy43+dz43*dz43;
            dx44             = ix4 - jx4;      
            dy44             = iy4 - jy4;      
            dz44             = iz4 - jz4;      
            rsq44            = dx44*dx44+dy44*dy44+dz44*dz44;
            rinv11           = 1.0/sqrt(rsq11);
            rinv22           = 1.0/sqrt(rsq22);
            rinv23           = 1.0/sqrt(rsq23);
            rinv24           = 1.0/sqrt(rsq24);
            rinv32           = 1.0/sqrt(rsq32);
            rinv33           = 1.0/sqrt(rsq33);
            rinv34           = 1.0/sqrt(rsq34);
            rinv42           = 1.0/sqrt(rsq42);
            rinv43           = 1.0/sqrt(rsq43);
            rinv44           = 1.0/sqrt(rsq44);
            rinvsq           = rinv11*rinv11;  
            rinvsix          = rinvsq*rinvsq*rinvsq;
            Vvdw6            = c6*rinvsix;     
            br               = cexp2*rsq11*rinv11;
            Vvdwexp          = cexp1*exp(-br); 
            Vvdwtot          = Vvdwtot+Vvdwexp-Vvdw6;
            fscal            = (br*Vvdwexp-6.0*Vvdw6)*rinvsq;
            tx               = fscal*dx11;     
            ty               = fscal*dy11;     
            tz               = fscal*dz11;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix1,iy1,iz1,jx1,jy1,jz1,tx,ty,tz);

            fix1             = fix1 + tx;      
            fiy1             = fiy1 + ty;      
            fiz1             = fiz1 + tz;      
            faction[j3+0]    = faction[j3+0] - tx;
            faction[j3+1]    = faction[j3+1] - ty;
            faction[j3+2]    = faction[j3+2] - tz;
            qq               = qqHH;           
            rinvsq           = rinv22*rinv22;  
            vcoul            = qq*rinv22;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx22;     
            ty               = fscal*dy22;     
            tz               = fscal*dz22;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix2,iy2,iz2,jx2,jy2,jz2,tx,ty,tz);

            fix2             = fix2 + tx;      
            fiy2             = fiy2 + ty;      
            fiz2             = fiz2 + tz;      
            fjx2             = faction[j3+3] - tx;
            fjy2             = faction[j3+4] - ty;
            fjz2             = faction[j3+5] - tz;
            qq               = qqHH;           
            rinvsq           = rinv23*rinv23;  
            vcoul            = qq*rinv23;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx23;     
            ty               = fscal*dy23;     
            tz               = fscal*dz23;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix2,iy2,iz2,jx3,jy3,jz3,tx,ty,tz);

            fix2             = fix2 + tx;      
            fiy2             = fiy2 + ty;      
            fiz2             = fiz2 + tz;      
            fjx3             = faction[j3+6] - tx;
            fjy3             = faction[j3+7] - ty;
            fjz3             = faction[j3+8] - tz;
            qq               = qqMH;           
            rinvsq           = rinv24*rinv24;  
            vcoul            = qq*rinv24;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx24;     
            ty               = fscal*dy24;     
            tz               = fscal*dz24;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix2,iy2,iz2,jx4,jy4,jz4,tx,ty,tz);

            fix2             = fix2 + tx;      
            fiy2             = fiy2 + ty;      
            fiz2             = fiz2 + tz;      
            fjx4             = faction[j3+9] - tx;
            fjy4             = faction[j3+10] - ty;
            fjz4             = faction[j3+11] - tz;
            qq               = qqHH;           
            rinvsq           = rinv32*rinv32;  
            vcoul            = qq*rinv32;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx32;     
            ty               = fscal*dy32;     
            tz               = fscal*dz32;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix3,iy3,iz3,jx2,jy2,jz2,tx,ty,tz);

            fix3             = fix3 + tx;      
            fiy3             = fiy3 + ty;      
            fiz3             = fiz3 + tz;      
            fjx2             = fjx2 - tx;      
            fjy2             = fjy2 - ty;      
            fjz2             = fjz2 - tz;      
            qq               = qqHH;           
            rinvsq           = rinv33*rinv33;  
            vcoul            = qq*rinv33;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx33;     
            ty               = fscal*dy33;     
            tz               = fscal*dz33;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix3,iy3,iz3,jx3,jy3,jz3,tx,ty,tz);

            fix3             = fix3 + tx;      
            fiy3             = fiy3 + ty;      
            fiz3             = fiz3 + tz;      
            fjx3             = fjx3 - tx;      
            fjy3             = fjy3 - ty;      
            fjz3             = fjz3 - tz;      
            qq               = qqMH;           
            rinvsq           = rinv34*rinv34;  
            vcoul            = qq*rinv34;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx34;     
            ty               = fscal*dy34;     
            tz               = fscal*dz34;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix3,iy3,iz3,jx4,jy4,jz4,tx,ty,tz);

            fix3             = fix3 + tx;      
            fiy3             = fiy3 + ty;      
            fiz3             = fiz3 + tz;      
            fjx4             = fjx4 - tx;      
            fjy4             = fjy4 - ty;      
            fjz4             = fjz4 - tz;      
            qq               = qqMH;           
            rinvsq           = rinv42*rinv42;  
            vcoul            = qq*rinv42;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx42;     
            ty               = fscal*dy42;     
            tz               = fscal*dz42;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix4,iy4,iz4,jx2,jy2,jz2,tx,ty,tz);

            fix4             = fix4 + tx;      
            fiy4             = fiy4 + ty;      
            fiz4             = fiz4 + tz;      
            faction[j3+3]    = fjx2 - tx;      
            faction[j3+4]    = fjy2 - ty;      
            faction[j3+5]    = fjz2 - tz;      
            qq               = qqMH;           
            rinvsq           = rinv43*rinv43;  
            vcoul            = qq*rinv43;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx43;     
            ty               = fscal*dy43;     
            tz               = fscal*dz43;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix4,iy4,iz4,jx3,jy3,jz3,tx,ty,tz);

            fix4             = fix4 + tx;      
            fiy4             = fiy4 + ty;      
            fiz4             = fiz4 + tz;      
            faction[j3+6]    = fjx3 - tx;      
            faction[j3+7]    = fjy3 - ty;      
            faction[j3+8]    = fjz3 - tz;      
            qq               = qqMM;           
            rinvsq           = rinv44*rinv44;  
            vcoul            = qq*rinv44;      
            vctot            = vctot+vcoul;    
            fscal            = (vcoul)*rinvsq; 
            tx               = fscal*dx44;     
            ty               = fscal*dy44;     
            tz               = fscal*dz44;     
            gmx_spread_local_virial_on_grid(localp_grid,

            ix4,iy4,iz4,jx4,jy4,jz4,tx,ty,tz);

            fix4             = fix4 + tx;      
            fiy4             = fiy4 + ty;      
            fiz4             = fiz4 + tz;      
            faction[j3+9]    = fjx4 - tx;      
            faction[j3+10]   = fjy4 - ty;      
            faction[j3+11]   = fjz4 - tz;      
        }
        
        faction[ii3+0]   = faction[ii3+0] + fix1;
        faction[ii3+1]   = faction[ii3+1] + fiy1;
        faction[ii3+2]   = faction[ii3+2] + fiz1;
        faction[ii3+3]   = faction[ii3+3] + fix2;
        faction[ii3+4]   = faction[ii3+4] + fiy2;
        faction[ii3+5]   = faction[ii3+5] + fiz2;
        faction[ii3+6]   = faction[ii3+6] + fix3;
        faction[ii3+7]   = faction[ii3+7] + fiy3;
        faction[ii3+8]   = faction[ii3+8] + fiz3;
        faction[ii3+9]   = faction[ii3+9] + fix4;
        faction[ii3+10]  = faction[ii3+10] + fiy4;
        faction[ii3+11]  = faction[ii3+11] + fiz4;
        fshift[is3]      = fshift[is3]+fix1+fix2+fix3+fix4;
        fshift[is3+1]    = fshift[is3+1]+fiy1+fiy2+fiy3+fiy4;
        fshift[is3+2]    = fshift[is3+2]+fiz1+fiz2+fiz3+fiz4;
        ggid             = gid[n];         
        Vc[ggid]         = Vc[ggid] + vctot;
        Vvdw[ggid]       = Vvdw[ggid] + Vvdwtot;
    }
    
    *outeriter       = nri;            
    *inneriter       = nj1;            
}





/*
 * Gromacs nonbonded kernel nb_kernel124nf
 * Coulomb interaction:     Normal Coulomb
 * VdW interaction:         Buckingham
 * water optimization:      pairs of TIP4P interactions
 * Calculate forces:        no
 */
void nb_kernel124nf(
                    int *           p_nri,
                    int *           iinr,
                    int *           jindex,
                    int *           jjnr,
                    int *           shift,
                    real *          shiftvec,
                    real *          fshift,
                    int *           gid,
                    real *          pos,
                    real *          faction,
                    real *          charge,
                    real *          p_facel,
                    real *          p_krf,
                    real *          p_crf,
                    real *          Vc,
                    int *           type,
                    int *           p_ntype,
                    real *          vdwparam,
                    real *          Vvdw,
                    real *          p_tabscale,
                    real *          VFtab,
                    real *          invsqrta,
                    real *          dvda,
                    real *          p_gbtabscale,
                    real *          GBtab,
                    int *           p_nthreads,
                    int *           count,
                    void *          mtx,
                    int *           outeriter,
                    int *           inneriter,
                    real *          work)
{
      gmx_localp_grid_t * localp_grid = (gmx_localp_grid_t *)work;
    int           nri,ntype,nthreads;
    real          facel,krf,crf,tabscale,gbtabscale;
    int           n,ii,is3,ii3,k,nj0,nj1,jnr,j3,ggid;
    real          shX,shY,shZ;
    real          rinvsq;
    real          qq,vcoul,vctot;
    int           tj;
    real          rinvsix;
    real          Vvdw6,Vvdwtot;
    real          Vvdwexp,br;
    real          ix1,iy1,iz1;
    real          ix2,iy2,iz2;
    real          ix3,iy3,iz3;
    real          ix4,iy4,iz4;
    real          jx1,jy1,jz1;
    real          jx2,jy2,jz2;
    real          jx3,jy3,jz3;
    real          jx4,jy4,jz4;
    real          dx11,dy11,dz11,rsq11,rinv11;
    real          dx22,dy22,dz22,rsq22,rinv22;
    real          dx23,dy23,dz23,rsq23,rinv23;
    real          dx24,dy24,dz24,rsq24,rinv24;
    real          dx32,dy32,dz32,rsq32,rinv32;
    real          dx33,dy33,dz33,rsq33,rinv33;
    real          dx34,dy34,dz34,rsq34,rinv34;
    real          dx42,dy42,dz42,rsq42,rinv42;
    real          dx43,dy43,dz43,rsq43,rinv43;
    real          dx44,dy44,dz44,rsq44,rinv44;
    real          qH,qM,qqMM,qqMH,qqHH;
    real          c6,cexp1,cexp2;

    nri              = *p_nri;         
    ntype            = *p_ntype;       
    nthreads         = *p_nthreads;    
    facel            = *p_facel;       
    krf              = *p_krf;         
    crf              = *p_crf;         
    tabscale         = *p_tabscale;    
    ii               = iinr[0];        
    qH               = charge[ii+1];   
    qM               = charge[ii+3];   
    qqMM             = facel*qM*qM;    
    qqMH             = facel*qM*qH;    
    qqHH             = facel*qH*qH;    
    tj               = 3*(ntype+1)*type[ii];
    c6               = vdwparam[tj];   
    cexp1            = vdwparam[tj+1]; 
    cexp2            = vdwparam[tj+2]; 

    nj1              = 0;              
    
    for(n=0; (n<nri); n++)
    {
        is3              = 3*shift[n];     
        shX              = shiftvec[is3];  
        shY              = shiftvec[is3+1];
        shZ              = shiftvec[is3+2];
        nj0              = jindex[n];      
        nj1              = jindex[n+1];    
        ii               = iinr[n];        
        ii3              = 3*ii;           
        ix1              = shX + pos[ii3+0];
        iy1              = shY + pos[ii3+1];
        iz1              = shZ + pos[ii3+2];
        ix2              = shX + pos[ii3+3];
        iy2              = shY + pos[ii3+4];
        iz2              = shZ + pos[ii3+5];
        ix3              = shX + pos[ii3+6];
        iy3              = shY + pos[ii3+7];
        iz3              = shZ + pos[ii3+8];
        ix4              = shX + pos[ii3+9];
        iy4              = shY + pos[ii3+10];
        iz4              = shZ + pos[ii3+11];
        vctot            = 0;              
        Vvdwtot          = 0;              
        
        for(k=nj0; (k<nj1); k++)
        {
            jnr              = jjnr[k];        
            j3               = 3*jnr;          
            jx1              = pos[j3+0];      
            jy1              = pos[j3+1];      
            jz1              = pos[j3+2];      
            jx2              = pos[j3+3];      
            jy2              = pos[j3+4];      
            jz2              = pos[j3+5];      
            jx3              = pos[j3+6];      
            jy3              = pos[j3+7];      
            jz3              = pos[j3+8];      
            jx4              = pos[j3+9];      
            jy4              = pos[j3+10];     
            jz4              = pos[j3+11];     
            dx11             = ix1 - jx1;      
            dy11             = iy1 - jy1;      
            dz11             = iz1 - jz1;      
            rsq11            = dx11*dx11+dy11*dy11+dz11*dz11;
            dx22             = ix2 - jx2;      
            dy22             = iy2 - jy2;      
            dz22             = iz2 - jz2;      
            rsq22            = dx22*dx22+dy22*dy22+dz22*dz22;
            dx23             = ix2 - jx3;      
            dy23             = iy2 - jy3;      
            dz23             = iz2 - jz3;      
            rsq23            = dx23*dx23+dy23*dy23+dz23*dz23;
            dx24             = ix2 - jx4;      
            dy24             = iy2 - jy4;      
            dz24             = iz2 - jz4;      
            rsq24            = dx24*dx24+dy24*dy24+dz24*dz24;
            dx32             = ix3 - jx2;      
            dy32             = iy3 - jy2;      
            dz32             = iz3 - jz2;      
            rsq32            = dx32*dx32+dy32*dy32+dz32*dz32;
            dx33             = ix3 - jx3;      
            dy33             = iy3 - jy3;      
            dz33             = iz3 - jz3;      
            rsq33            = dx33*dx33+dy33*dy33+dz33*dz33;
            dx34             = ix3 - jx4;      
            dy34             = iy3 - jy4;      
            dz34             = iz3 - jz4;      
            rsq34            = dx34*dx34+dy34*dy34+dz34*dz34;
            dx42             = ix4 - jx2;      
            dy42             = iy4 - jy2;      
            dz42             = iz4 - jz2;      
            rsq42            = dx42*dx42+dy42*dy42+dz42*dz42;
            dx43             = ix4 - jx3;      
            dy43             = iy4 - jy3;      
            dz43             = iz4 - jz3;      
            rsq43            = dx43*dx43+dy43*dy43+dz43*dz43;
            dx44             = ix4 - jx4;      
            dy44             = iy4 - jy4;      
            dz44             = iz4 - jz4;      
            rsq44            = dx44*dx44+dy44*dy44+dz44*dz44;
            rinv11           = 1.0/sqrt(rsq11);
            rinv22           = 1.0/sqrt(rsq22);
            rinv23           = 1.0/sqrt(rsq23);
            rinv24           = 1.0/sqrt(rsq24);
            rinv32           = 1.0/sqrt(rsq32);
            rinv33           = 1.0/sqrt(rsq33);
            rinv34           = 1.0/sqrt(rsq34);
            rinv42           = 1.0/sqrt(rsq42);
            rinv43           = 1.0/sqrt(rsq43);
            rinv44           = 1.0/sqrt(rsq44);
            rinvsq           = rinv11*rinv11;  
            rinvsix          = rinvsq*rinvsq*rinvsq;
            Vvdw6            = c6*rinvsix;     
            br               = cexp2*rsq11*rinv11;
            Vvdwexp          = cexp1*exp(-br); 
            Vvdwtot          = Vvdwtot+Vvdwexp-Vvdw6;
            qq               = qqHH;           
            vcoul            = qq*rinv22;      
            vctot            = vctot+vcoul;    
            qq               = qqHH;           
            vcoul            = qq*rinv23;      
            vctot            = vctot+vcoul;    
            qq               = qqMH;           
            vcoul            = qq*rinv24;      
            vctot            = vctot+vcoul;    
            qq               = qqHH;           
            vcoul            = qq*rinv32;      
            vctot            = vctot+vcoul;    
            qq               = qqHH;           
            vcoul            = qq*rinv33;      
            vctot            = vctot+vcoul;    
            qq               = qqMH;           
            vcoul            = qq*rinv34;      
            vctot            = vctot+vcoul;    
            qq               = qqMH;           
            vcoul            = qq*rinv42;      
            vctot            = vctot+vcoul;    
            qq               = qqMH;           
            vcoul            = qq*rinv43;      
            vctot            = vctot+vcoul;    
            qq               = qqMM;           
            vcoul            = qq*rinv44;      
            vctot            = vctot+vcoul;    
        }
        
        ggid             = gid[n];         
        Vc[ggid]         = Vc[ggid] + vctot;
        Vvdw[ggid]       = Vvdw[ggid] + Vvdwtot;
    }
    
    *outeriter       = nri;            
    *inneriter       = nj1;            
}


