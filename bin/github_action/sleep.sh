if [ "$GITHUB_EVENT_NAME" != "workflow_dispatch" ] 
then 
  echo "random sleep 1-10000 seconds." && sleep $[($RANDOM % 10000)+1]
fi
