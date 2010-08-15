int find(int level)
{
	int i,j;
	signa[level]=1;
	for(i=1;i<=ny;i++)
		if(signb[i]==0&&(lx[level]+ly[i]==map[level][i]))
		{
			signb[i]=1;
			if(linkb[i]==-1||find(linkb[i]))
			{
				linkb[i]=level;
				linka[level]=i;
				return 1;
			}
		}
		return 0;
}
int KM()
{
	int i,j,k,d,ans;
	//memset(lx,-INF,sizeof(lx));
	memset(ly,0,sizeof(ly));
	memset(linka,-1,sizeof(linka));
	memset(linkb,-1,sizeof(linkb));
	for(i=1;i<=nx;i++)
	{
		lx[i]=-INF;
		for(j=1;j<=ny;j++)
		{
			lx[i]>?=map[i][j];
		}
		// printf("%d ",lx[i]);
	}
	for(i=1;i<=nx;i++)
	{
		while(1)
		{
			// printf("dsds");
			memset(signa,0,sizeof(signa));
			memset(signb,0,sizeof(signb));
			if(find(i))
			{
				// printf("dsds");
				break;
			}
			// printf("sdsd");
			d=INF;
			for(j=1;j<=nx;j++)
				if(signa[j])
				{
					for(k=1;k<=ny;k++)
						if(signb[k]==0)
						{
							d<?=lx[j]+ly[k]-map[j][k];
						}
				}
				for(j=1;j<=nx;j++)
					if(signa[j])
						lx[j]-=d;
				for(j=1;j<=ny;j++)
					if(signb[j])
						ly[j]+=d;
		}
	}
	ans=0;
	for(i=1;i<=nx;i++)
		ans+=map[i][linka[i]];
	return -ans;
}

