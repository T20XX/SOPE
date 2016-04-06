int isEqual(struct simp_file *files, int size){

	int i, j;
	for(i = 0; i < size; i++){
		for(j = i; j < size; j++){
			if(strcmp(files[i].name, files[j].name) == 0){
				if(strcmp(files[i].permissions, files[j].permissions) == 0){
					if(strcmp(files[i].size, files[j].size) == 0){
						//if(programa.auxiliar());{
						if(files[i].date < files[j].date){
								link(files[j].path, files[i].path);	
							} else {
								link(files[i].path, files[j].path);
							}
						//}
					}
				}
			}
		}
	}
} 