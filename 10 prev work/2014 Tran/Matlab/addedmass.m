% Find the added mass.
% http://books.google.no/books?id=UbjvXKReIAUC&pg=PA36&lpg=PA36&dq=added+ma
% ss+surge&source=bl&ots=oKifgyfN8l&sig=wv2lxhieZTK9Qx9i4IJkQSErlsk&hl=no&ei=wcOqTe-SE83NsgbZ3OiWCA&sa=X&oi=book_result&ct=result&resnum=3&ved=0CCwQ6AEwAg#v=onepage&q=added%20mass%20surge&f=false

d=0.248/2;
L=1.105;

e=sqrt(1-((d^2)/(L^2)));

a_0=(2*(1-e^2)/e^3)*(0.5*log((1+e)/(1-e)) -e);
b_0=(1/(e^2))- ((1-e^2)/(2*e^3))*log((1+e)/(1-e));


k_1=a_0/(2-a_0);
k_2=b_0/(2-b_0);



A_11=14.1*k_1
A_22=14.1*k_2