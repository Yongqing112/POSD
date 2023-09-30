# __Gitlab Setting__

### 1. The username and password is your student id. Login to [GitLab (http://140.124.181.100)](http://140.124.181.100) and modify your password.
![Login](./img/gitlab/signIn.png)
### 2. Select "Create a project" to create a new project.

**Important**:
1. The project name must to be **\posd2023f_\${STUDENT_ID}_HW**.  

2. Set project visibility level as **private**.  

  ![Select Create Project](./img/gitlab/selectCreate.png)
  ![Create Project](./img/gitlab/createProject.png)

### 3. Authorize TA to access your repository

1. Go to Members  
    ![Members](./img/gitlab/members.png)
1. Search posd2023ta
    ![SearchTA](./img/gitlab/searchTA.png)
1. Choose *Maintainer* as role permission, and click invite  
    ![Invite TA](./img/gitlab/inviteTA.png)
1. You can find out There's 2 more members  
    ![TA invited](./img/gitlab/TAinvited.png)


### 4. Set webhook

1. Go to **Setting -> Webhooks**<br>
    ![gitlab integration](./img/gitlab/gitlabWebhook.png)

2. Fill in url as: "http://root:1161a7e2d616f4388e1e9b3d3737b485c9@140.124.181.97:8080/project/posd2023f_${STUDENT_ID}_HW"

3. Keep Secret Token as empty.

4. Select **Push events** in Trigger selection

5. Unselect **Enable SSL verification** in SSL verification.

6. Click "Add webhook"

    ![webhook](./img/gitlab/webhookSetting.png)
