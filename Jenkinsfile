pipeline {
    agent { label 'jenkins1' }
    environment {
        PATH = "${env.WORKSPACE}/venv/bin:${env.PATH}"
    }
    stages {
        stage('Initialize') {
            steps {
                echo 'Initializing...'
                // Ensure pip and virtualenv are installed
                sh 'python3 -m pip install --upgrade pip'
                sh 'pip install virtualenv'
                // Create and activate virtual environment
                sh 'python3 -m venv venv'
                // Install dependencies from requirements.txt and additional plugins
                sh '''
                . venv/bin/activate
                pip install -r requirements.txt
                pip install pytest-html pytest-metadata
                '''
            }
        }
        stage('Verification') {
            parallel {
                stage('Unit Test') {
                    steps {
                        echo 'Running target test...'
                        sh '''
                        . venv/bin/activate
                        pytest ./com.X/test/test_target_test.py --html=unit_test_report.html --self-contained-html
                        '''
                    }
                }
            }
        }
    }
    post {
        always {
            echo 'Archiving logs...'
            // Archive the test reports regardless of the build result
            archiveArtifacts artifacts: '*.html', allowEmptyArchive: true
        }
    }
}
