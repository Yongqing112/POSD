# Steps for hand in assignments

1. (First time only) Open a terminal/cmd and `cd` to the directory you want to place your assignment project.

    ```shell
    $ cd /path/to/your/workspace
    ```

2. (First time only) Clone your own homework repository from GitLab to your workspace.

    ```shell
    $ git clone http://140.124.181.100/${STUDENT_ID}/posd2023f_${STUDENT_ID}_hw.git
    ```

3. Enter the assignment project in the terminal/cmd.

   ```shell
   $ cd /path/to/your/workspace/posd2023f_${STUDENT_ID}_hw
   ```

4. Edit the source code to reach the assignment requirements.

5. Stage the changes for the new commit.

    ```shell
    $ git add .
    ```

6. Commit changes.

   ```shell
   $ git commit -m "${COMMIT_MESSAGE}"
   ```

   For the users first time using git on the device, enter the following commands before commit:

   ```shell
   $ git config --global user.email "${YOUR_EMAIL}"
   $ git config --global user.name "${YOUR_NAME}"
   ```

7. Push changes to GitLab

    ```shell
    $ git push origin master
    ```

8. Go to [GitLab](http://140.124.181.100) to check if upload succeed.

9. Go to [Jenkins](http://140.124.181.97:8080) check for the build status. Check [Jenkins setup](./setup_tutorial/jenkins_setup.md) for further info.