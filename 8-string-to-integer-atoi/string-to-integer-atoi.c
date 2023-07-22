int myAtoi(char * s){
    printf("%ld",strtol(s,NULL,10));
    if(strtol(s,NULL,10)>2147483647){
        return(2147483647);
    }
    // herhangi bir numara olabilir strong olsun yeter
    else if(strtol(s,NULL,10)<=-2147483648){
        printf("Thiss is the case");
        return(-2147483648);
    }
    else{
        return(strtol(s,NULL,10));
    }
}