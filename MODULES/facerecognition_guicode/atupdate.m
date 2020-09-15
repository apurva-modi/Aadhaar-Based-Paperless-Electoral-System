function atupdate(a)
switch a        
        case 1
            a1=xlsread('database.xlsx',1,'C4') ;
        a1=a1+1;
        xlswrite('database.xlsx',a1,1,'C4');
        time=clock;
         xlswrite('database.xlsx',time,1,'D4');        
         
         case 2
            a1=xlsread('database.xlsx',1,'C5') ;
        a1=a1+1;
        xlswrite('database.xlsx',a1,1,'C5');
        time=clock;
         xlswrite('database.xlsx',time,1,'D5');
         
         
            case 3
            a1=xlsread('database.xlsx',1,'C6') ;
        a1=a1+1;
        xlswrite('database.xlsx',a1,1,'C6');
        time=clock;
         xlswrite('database.xlsx',time,1,'D6');       
         
         
         
    end