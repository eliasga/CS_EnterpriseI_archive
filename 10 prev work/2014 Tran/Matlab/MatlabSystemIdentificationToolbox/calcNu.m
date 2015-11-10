function nu = calcNu(eta6dof)
    for i=1:length(eta6dof)-1
        etadott=diff(eta6dof([i:i+1],:));
        R=Rzyx(eta6dof(i,4),eta6dof(i,5),eta6dof(i,6));
        nu_tmp=[R zeros(3); zeros(3) R]*(etadott');
        nu(i,[1:6])=nu_tmp';
    end
end