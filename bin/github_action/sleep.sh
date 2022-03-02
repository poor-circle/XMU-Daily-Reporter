if [ $GITHUB_EVENT_NAME != "workflow_dispatch" ]
then
  echo "random sleep 0-2 hours." && sleep $[($RANDOM % 7200)+1]
else
  echo "workflow dispath manually, skip sleeping."
fi

