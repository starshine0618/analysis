# -*- coding: utf-8 -*-
import numpy as np
 
def LCS(s1,s2):
    dp = np.zeros((len(s1)+1,len(s2)+1))  
    for i in range(1, len(s1)+1):
        for j in range(1, len(s2)+1):
            if s1[i-1]==s2[j-1]:
                dp[i][j]=dp[i-1][j-1]+1
            else:
                dp[i][j]=max(dp[i-1][j],dp[i][j-1])
    return dp
 
def GetLCS(i,j,dp,s1,s2,s):
    while i>0 and j>0:
        if s1[i-1]==s2[j-1]:
            s+=s1[i-1]
            i-=1
            j-=1
        else:
            if dp[i-1][j]>dp[i][j-1]:
                i-=1
            elif dp[i-1][j]<dp[i][j-1]:
                j-=1
            else:
               GetLCS(i-1,j,dp,s1,s2,s)
               GetLCS(i,j-1,dp,s1,s2,s)
               return
    print(s[::-1])
 
if __name__ == '__main__':
    s1 = '122456'
    s2 = '122486'
    s=''
    dp = LCS(s1,s2)
    GetLCS(len(s1),len(s2),dp,s1,s2,s)